# Urho3D Android Project
  
---
### Description
Android project to load specific C++ executable file directly instead of Urho3DPlayer. If you're a C++ developer and want to load your C++ exectuable instead of Urho3DPlayer, this project might be what you're looking for.

---
### Implementation Info
* SDLActivity loads and runs 75_JoyStickAndroid (C++) executable sample directly, happens here https://github.com/Lumak/Urho3D-Android-Project/blob/master/Android/src/org/libsdl/app/SDLActivity.java#L71
* Demonstrates request process to the SDLActivity from C++.
* Demonstrates callback process from the SDLActivity to C++.
  
---
### Build Steps
This project is based on Urho3D 1.7 release. Follow the build steps below.  
I'm using **android-ndk-r15c** for this project. My understanding is that there is a build issue with ndk-r16.

1) Download the Urho3D 1.7 tag, https://github.com/urho3d/Urho3D/tree/1.7 , unzip it and rename the folder to something like Urho3D-1.7-AndroidTest or whatever your preference.

2) Delete the following folders (**required**):  
* Android/res/layout
* Android/src/com/github
* In the Source/Samples/ folder, delete all samples from 01 to 47

3) Copy the contents of this project into your new Urho3D folder.

4) Build using either cmake_android-arm.bat or cmake_android-x86.bat.  
If you're on Linux or OSX, copy the flags from one of the included batch file into your .sh file.  
At the command prompt type:
```
cmake_android-arm.bat *your-build-path*
```  

5) Go into your *your-build-path* and at the command prompt type:
```
make
```

6) Once built, go into *your-build-path*/assets/ folder and delete the Autoload shortcut. It's not necessary to load the 39 MB of data that you won't use.

7) follow the Android Studio import process below.

### Android Studio Import
Android Studio 3.0 is used in this example.
1) Start Android Studio and select new->Import Project...

2) Select your *your-build-path* folder then OK.

3) Select destination folder and OK to default settigs.

4) You'll encouter a gradle error, something that looks like:  
*Error:Minimum supported Gradle version is 4.1. Current version is 2.14.1. If using the gradle wrapper, try editing the distributionUrl in C:\Users\<yourname>\AndroidStudioProjects\<your-build-path>\gradle\wrapper\gradle-wrapper.properties to gradle-4.1-all.zip*  

Fix the error by:  

![alt tag](https://github.com/Lumak/Urho3D-Android-Project/blob/master/screenshot/gradle-error.jpg)  

5) Build and Run app

6) Select an AVD emulation device or your Android phone.
  
### Multiple Android Architecture Support
You don't need to create additional Android Studio project to do this. All you need to do is repeat build steps 4 and 5 for a different architecture and copy *your-alternate-build-path*/libs/*alternate architecture* folder to *your android project*/app/src/main/jniLibs folder.  
**Note:** you do need to create an alternate build path to do this and avoid over writing your first build.

---  
### License
The MIT License (MIT)







