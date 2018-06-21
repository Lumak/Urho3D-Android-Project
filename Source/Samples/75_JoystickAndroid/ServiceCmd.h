//
// Copyright (c) 2008-2016 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#pragma once

#include <Urho3D/Core/Object.h>

using namespace Urho3D;

namespace Urho3D
{
class Controls;
}

//=============================================================================
//=============================================================================
enum ServiceCommands
{
    // test enums used by characterdemo
    MIN_COMMAND = 6,

    COMMAND_TEST1 = 6,
    COMMAND_TEST2 = 7,
    COMMAND_TEST3 = 8,
    COMMAND_TEST4 = 9,

    MAX_COMMANS = 9,
};

//=============================================================================
//=============================================================================
URHO3D_EVENT(E_SERVICE_MESSAGE, ServiceMessage)
{
    URHO3D_PARAM(P_COMMAND, Command); // int
    URHO3D_PARAM(P_STATUS, Status);   // int
    URHO3D_PARAM(P_MESSAGE, Message); // String
}

//=============================================================================
//=============================================================================
class ServiceCmd : public Object
{
    URHO3D_OBJECT(ServiceCmd, Object);
public:
    ServiceCmd(Context* context);
    ~ServiceCmd();

    void SendCmdMessage(int cmd, int param);

protected:
    static void JavaActivityCallback(int ival, int istat, const char *pstr, void *param);
    void ActivityCallback(int val, int istat, const char *pstr);
    void ProcessMessageQueue();
    void HandleUpdate(StringHash eventType, VariantMap& eventData);

protected:


private:
    struct MessageData
    {
        int val_;
        int stat_;
        String message_;
    };

    Vector<MessageData> messageList_;
    Mutex               mutexMessageLock_;

    bool HasQueueMessage(MessageData& messageData);
    void PopFrontQueue();
    void SendResponseMsg(const MessageData &msg);
};

