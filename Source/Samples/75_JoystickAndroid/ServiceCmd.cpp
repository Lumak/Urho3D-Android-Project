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

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Core/ProcessUtils.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/IO/Log.h>

#include "ServiceCmd.h"

#include <Urho3D/DebugNew.h>
//=============================================================================
//=============================================================================
#if defined(__ANDROID__)
#include <SDL/SDL.h>
extern "C"
{
int Android_JNI_SendMessage(int command, int param);
}

#else
// create dummy interface for all non-Android platforms
typedef void (*UserActivityCallback)(int id1, int istat, const char *str, void *param);
void SDL_RegisterUserActivityCallback(UserActivityCallback callback, void *param){}
int Android_JNI_SendMessage(int command, int param){ return 0; }
#endif

//=============================================================================
//=============================================================================
ServiceCmd::ServiceCmd(Context* context)
    : Object(context)
{
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(ServiceCmd, HandleUpdate));
    SDL_RegisterUserActivityCallback(&ServiceCmd::JavaActivityCallback, this);
}

ServiceCmd::~ServiceCmd()
{
    SDL_RegisterUserActivityCallback(NULL, NULL);
}

void ServiceCmd::JavaActivityCallback(int ival, int istat, const char *pstr, void *param)
{
    if (param)
    {
        ((ServiceCmd*)param)->ActivityCallback(ival, istat, pstr);
    }
}

void ServiceCmd::SendCmdMessage(int cmd, int param)
{
    Android_JNI_SendMessage(cmd, param);
}

void ServiceCmd::ActivityCallback(int val, int stat, const char *pstr)
{
    MutexLock lock(mutexMessageLock_);

    messageList_.Resize(messageList_.Size() + 1);
    MessageData &messageData = messageList_[messageList_.Size() - 1];

    messageData.val_     = val;
    messageData.stat_    = stat;
    messageData.message_ = pstr?String(pstr):String::EMPTY;
}

bool ServiceCmd::HasQueueMessage(MessageData& messageData)
{
    MutexLock lock(mutexMessageLock_);

    bool hasData = false;

    if (messageList_.Size())
    {
        messageData = messageList_[0];
        hasData = true;
    }

    return hasData;
}

void ServiceCmd::PopFrontQueue()
{
    MutexLock lock(mutexMessageLock_);

    if (messageList_.Size())
    {
        messageList_.Erase(0);
    }
}

void ServiceCmd::SendResponseMsg(const MessageData &msg)
{
    using namespace ServiceMessage;

    VariantMap& eventData = GetEventDataMap();
    eventData[P_COMMAND]  = msg.val_;
    eventData[P_STATUS]   = msg.stat_;
    eventData[P_MESSAGE]  = msg.message_;

    SendEvent(E_SERVICE_MESSAGE, eventData);
}

void ServiceCmd::ProcessMessageQueue()
{
    MessageData messageData;

    while (HasQueueMessage(messageData))
    {
        SendResponseMsg(messageData);
        PopFrontQueue();
    }
}

void ServiceCmd::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;

    ProcessMessageQueue();
}



