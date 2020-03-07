
#ifndef BUFFERED_CHANNEL_H_
#define BUFFERED_CHANNEL_H_

#include <queue>
#include <mutex>
#include <utility>
#include <condition_variable>

template<class T>
class BufferedChannel {
public:
    explicit BufferedChannel(size_t size): BufferSize(size),IsClose(false){}

    void Send(T value) {
        std::unique_lock<std::mutex> lock(Mutex);
        if(IsClose){
            throw std::runtime_error("Channel is close");
        }
        if(Queue.size()<BufferSize){
            Queue.push(std::move(value));
            RecvVariable.notify_one();
        }
        else {
            while(Queue.size() == BufferSize && !IsClose) {
                SendVariable.wait(lock);
            }
            if(IsClose){
                throw std::runtime_error("Channel is close");
            }
            else{
                Queue.push(std::move(value));
                RecvVariable.notify_one();
            }
        }
    }

    std::pair<T, bool> Recv() {
        std::unique_lock<std::mutex> lock(Mutex);
        while (Queue.size()==0 && !IsClose)
        {
            RecvVariable.wait(lock);
        }
        if(Queue.size()==0){
            return std::make_pair( T(),false);
        }
        T res=Queue.front();
        Queue.pop();
        SendVariable.notify_one();
        return std::make_pair(res, true);
    }

    void Close() {
        std::unique_lock<std::mutex> lock(Mutex);
        IsClose=true;
        SendVariable.notify_all();
        RecvVariable.notify_all();
    }

private:
    std::queue<T> Queue;
    size_t BufferSize;
    std::mutex Mutex;
    bool IsClose;
    std::condition_variable RecvVariable;
    std::condition_variable SendVariable;
};

#endif // BUFFERED_CHANNEL_H_
