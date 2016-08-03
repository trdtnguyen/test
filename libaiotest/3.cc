// Code written by Daniel Ehrenberg, released into the public domain

#include <fcntl.h>
//#include <gflags/gflags.h>
//#include <glog/logging.h>
#include <libaio.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PATH "/tmp/testfile"
#define FILE_SIZE 1000
#define NUM_CREQUEST 100
#define MIN_NR 1
#define MAX_NR 1

//The size of the operation that will occur on the device
static const int PAGE_SIZE = 4096;

class AIORequest {
		public:
			int *_buffer;

			virtual void complete(int res) = 0;

			AIORequest() {
				//each request has a 1-page-size buffer
				int ret = posix_memalign(reinterpret_cast<void**>(&_buffer),
						PAGE_SIZE, PAGE_SIZE);
			}

			virtual ~AIORequest() {
				free(_buffer);
			}	
};

class Adder {
		public:
			virtual void add(int amount) = 0;

			virtual ~Adder() {};
};

class AIOReadRequest : public AIORequest {
		private:
			Adder *_adder;

		public:
			AIOReadRequest (Adder *adder) : AIORequest(), _adder (adder) {}
//implement complete(1) function 
			virtual void complete(int res) {
				int value = _buffer[0];
				_adder->add(value);
			}			
};

class AIOWriteRequest : public AIORequest{
	private:
		int _value;

	public:
		AIOWriteRequest(int value) : AIORequest(), _value(value){
				_buffer[0] = value;
		}

		virtual void complete(int res){
			//do nothing
		}
};
/*
//Major class perform libaio functions
*/
class AIOAdder : public Adder {
		public:
			int _fd;
			io_context_t _ioctx;

			int _counter;
			int _reap_counter;
			int _sum;
			int _length;

			AIOAdder(int length) : _ioctx(0), _counter(0), _reap_counter(0),
			_sum(0), _length(length){}

			//Get the io context by using io_setup()
			void init() {
				_fd = open(PATH, O_RDWR | O_DIRECT | O_CREAT, 0644);
				if( _fd < 0) {
					perror("Error opening file");
					return ;
				}
				if(fallocate( _fd, 0, 0, PAGE_SIZE * _length) < 0){
					printf("Error in fallocate");
					return ;
				}

				io_setup(100, &_ioctx);
			}

			virtual void add(int amount){
				_sum += amount;
			}

			/*for each submitWrite() call
			 * 1. create new AIOWriteRequest,
			 * 2. init iocb struct
			 * 3. call io_submit
			 * */
			void submitWrite(int data) {
				struct iocb iocb;
				struct iocb* iocbs = &iocb;
				AIORequest *req = new AIOWriteRequest(data);
				//init values for iocb bu call io_prep_pwrite
				io_prep_pwrite(&iocb, _fd, req->_buffer, PAGE_SIZE, _counter * PAGE_SIZE);
				iocb.data = req;
				int res = io_submit(_ioctx, 1, &iocbs);		
			}
		 
			/*
			 *write serial of numbers 0, 1, 2, ..., length on file
			 * */
			void writeFile() {
					_reap_counter = 0;
			    for (_counter = 0; _counter < _length; _counter++) {
					      submitWrite(_counter);
					      reap();
			    }
			    reapRemaining();
			}

			void readFile(){
				_reap_counter = 0;
		    for (_counter = 0; _counter < _length; _counter++) {
		        submitRead();
		        reap();
		    }
		    reapRemaining();
			}
			/*
			 *for each submitRead() call
			 1. Create AIOReadRequest
			 2. Init iocb struct by using io_prep_pread()
			 3. call io_submit() to submit the request
			 * */
			void submitRead() {
				struct iocb iocb;
		    struct iocb* iocbs = &iocb;
		    AIORequest *req = new AIOReadRequest(this);
		    io_prep_pread(&iocb, _fd, req->_buffer, PAGE_SIZE, _counter * PAGE_SIZE);
		    iocb.data = req;
		    int res = io_submit(_ioctx, 1, &iocbs);
			}


			void reap() {
					if (_counter >= MIN_NR) {
				      doReap(MIN_NR);
			    }
			}
			int doReap(int min_nr){
				struct io_event* events = new io_event[MAX_NR];
		    struct timespec timeout;
		    timeout.tv_sec = 0;
		    timeout.tv_nsec = 100000000;
		    int num_events;
				num_events = io_getevents(_ioctx, min_nr, MAX_NR, events, &timeout);
				for (int i = 0; i < num_events; i++) {
				     struct io_event event = events[i];
				     AIORequest* req = static_cast<AIORequest*>(event.data);
  			     req->complete(event.res);
				     delete req;
		    }
		    delete events;
																						    
		    _reap_counter += num_events;
				return num_events;
			}


			void reapRemaining() {
					while (_reap_counter < _length) {
				      doReap(1);
					}
			}

			~AIOAdder() {
				io_destroy(_ioctx);
				close(_fd);
			}

			int sum() {
				writeFile();
				readFile();
				return _sum;
			}
};

int main(int argc, char* argv[]){

		AIOAdder adder_obj(FILE_SIZE);
		adder_obj.init();
		int sum = adder_obj.sum();
		int expected = (FILE_SIZE * (FILE_SIZE - 1)) / 2;
		printf("Successfully calculated that the sum of integers from 0 to %d is %d\n",
				FILE_SIZE - 1, sum);
		return 0;
}
