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
#include <SDL/SDL_gamecontroller.h>

using namespace Urho3D;

namespace Urho3D
{
class Controls;
}

//=============================================================================
//=============================================================================
const StringHash VAR_AXIS_0("VAR_AXIS_0");
const StringHash VAR_AXIS_1("VAR_AXIS_1");
const StringHash VAR_AXIS_2("VAR_AXIS_2");

const unsigned BUTTON_A             = (1 << SDL_CONTROLLER_BUTTON_A            );
const unsigned BUTTON_B             = (1 << SDL_CONTROLLER_BUTTON_B            );
const unsigned BUTTON_X             = (1 << SDL_CONTROLLER_BUTTON_X            );
const unsigned BUTTON_Y             = (1 << SDL_CONTROLLER_BUTTON_Y            );
const unsigned BUTTON_BACK          = (1 << SDL_CONTROLLER_BUTTON_BACK         );
const unsigned BUTTON_GUIDE         = (1 << SDL_CONTROLLER_BUTTON_GUIDE        );
const unsigned BUTTON_START         = (1 << SDL_CONTROLLER_BUTTON_START        );
const unsigned BUTTON_LEFTSTICK     = (1 << SDL_CONTROLLER_BUTTON_LEFTSTICK    );
const unsigned BUTTON_RIGHTSTICK    = (1 << SDL_CONTROLLER_BUTTON_RIGHTSTICK   );
const unsigned BUTTON_LEFTSHOULDER  = (1 << SDL_CONTROLLER_BUTTON_LEFTSHOULDER );
const unsigned BUTTON_RIGHTSHOULDER = (1 << SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
const unsigned BUTTON_DPAD_UP       = (1 << SDL_CONTROLLER_BUTTON_DPAD_UP      );
const unsigned BUTTON_DPAD_DOWN     = (1 << SDL_CONTROLLER_BUTTON_DPAD_DOWN    );
const unsigned BUTTON_DPAD_LEFT     = (1 << SDL_CONTROLLER_BUTTON_DPAD_LEFT    );
const unsigned BUTTON_DPAD_RIGHT    = (1 << SDL_CONTROLLER_BUTTON_DPAD_RIGHT   );

//=============================================================================
//=============================================================================
const float CAMERA_MIN_DIST = 1.0f;
const float CAMERA_INITIAL_DIST = 5.0f;
const float CAMERA_MAX_DIST = 20.0f;

//=============================================================================
//=============================================================================
class GameController : public Object
{
    URHO3D_OBJECT(GameController, Object);

public:
    GameController(Context* context);
    ~GameController();

    void UpdateControlInputs(Controls& controls);

    bool IsValid() const                { return joystickID_ != -1; }
    void SetMinTolerance(float minVal)  { minTolerance_ = minVal; }
    float GetMinTolerance() const       { return minTolerance_; }
    void DumpAll() const;

protected:
    void SetupControllerMaps();
    bool CreateController();
    void RemoveScreenJoystick();
    void ClampValues(Vector2 &vec, float minVal) const;
    void DumpControllerInfo(unsigned idx, bool useIdx=false) const;
    void HandleJoystickConnected(StringHash eventType, VariantMap& eventData);
    void HandleJoystickDisconnected(StringHash eventType, VariantMap& eventData);

protected:
    int joystickID_;
    float minTolerance_;
};

