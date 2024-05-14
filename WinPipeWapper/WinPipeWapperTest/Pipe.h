/*
Pipe.h
Written by Matthew Fisher

A pipe is a connection between two programs, possibly on different computers.
*/
#include <string>
 
class Pipe
{
public:
    Pipe();
    ~Pipe();
    //
    // Connection
    //
    void ClosePipe();
    bool CreatePipe(const std::string &PipeName, UINT PipeBufferSize = 100000);
    bool ConnectToLocalPipe(const std::string &PipeName);
    bool ConnectToPipe(const std::string &PipeName);

    //
    // Messaging
    //
    bool MessagePresent();
    bool ReadMessage(std::string &strRead);
    bool PipeSendMessage(const BYTE *Message, UINT MessageLength);
	bool PipeSendMessage(const std::string &Message);

    //
    // Query
    //
    UINT ActiveInstances();
    std::string UserName();
    __forceinline bool Valid()
    {
        return (_Handle != NULL);
    }
    
private:
    HANDLE _Handle;
};
