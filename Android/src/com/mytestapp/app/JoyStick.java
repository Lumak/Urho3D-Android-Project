//=============================================================================
// list your package
//=============================================================================
package com.mytestapp.app;

// R string value
import com.mytestapp.app.R;

//=============================================================================
// imports
//=============================================================================
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

import org.libsdl.app.SDLActivity;

import android.content.Intent;

import android.widget.RelativeLayout;
import android.content.*;
import android.view.*;
import android.os.*;
import android.util.Log;

//=============================================================================
// JoyStick class
//=============================================================================
public class JoyStick extends SDLActivity{

    // func overrides
    @Override
    protected void InitializeApp(){
    }

    @Override
    protected void PauseApp() {
    }

    @Override
    protected void ResumeApp() {
    }

    @Override
    protected void DestroyApp(){
    }

    @Override
    protected boolean onProcessUserCommand(int command, Object param) {

        boolean bresult = false;
        int iParam = (int)param;

        switch (command) 
        {
        case COMMAND_TEST1:
            // do some java process

            // then notify your app
            nativeUserActivityCallback(COMMAND_TEST1, 0, "Hello World!");
            bresult = true;
            break;

        case COMMAND_TEST2:
            // do some java process

            // then notify your app
            nativeUserActivityCallback(COMMAND_TEST2, 0, "Test 2");
            bresult = true;
            break;

        case COMMAND_TEST3:
            // do some java process

            // then notify your app
            nativeUserActivityCallback(COMMAND_TEST3, 0, "Test 3");
            bresult = true;
            break;

        case COMMAND_TEST4:
            // do some java process

            // then notify your app
            nativeUserActivityCallback(COMMAND_TEST4, 0, "");
            bresult = true;
            break;

        default:
        }

        return bresult;
    }

    // Messages from the SDLMain thread
    //static final int COMMAND_CHANGE_TITLE = 1;
    //static final int COMMAND_UNUSED = 2;
    //static final int COMMAND_TEXTEDIT_HIDE = 3;
    //static final int COMMAND_SET_KEEP_SCREEN_ON = 5;

    // test constants
    static final int COMMAND_TEST1 = 6;
    static final int COMMAND_TEST2 = 7;
    static final int COMMAND_TEST3 = 8;
    static final int COMMAND_TEST4 = 9;

}
