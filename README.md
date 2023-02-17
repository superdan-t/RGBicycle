# RGBicycle
## Deprecated Project Notice
I have not updated or otherwise maintained this project since 2019, before going to college at all. I disassembled this project in 2022, so this code will never be used again. My program design skills, quality standards, language preferences, and other technical abilities have developed a lot since 2019, assisted by my interest in maintaining projects outside of academia. That being said, I have decided to keep my old projects public as I reflect on my own educational journey.

## Project Description
I decided it would be fun to attach nearly 15 full feet of RGB LED strips to my mountain bike. The lights were battery-powered and controlled by two tandem Arduino Nanos. One Nano was connected to a Bluetooth module so I could select colors and effects from a smartphone app.

The light effects were fun for a while, and this was a defining project for me to develop my creative style from. I disassembled this setup in 2022 because I rarely ride my bike in the late evenings anymore, so the lights were just extra weight, and the circuitry was rusting from low protection anyway.

## Technical Description
I used non-addressable LED strips with hand-soldered MOSFET drivers. There were a total of 12 MOSFETS, driving four regions of RGB LEDs. Two Arduino Nanos worked together to switch them: one as the primary controller, which handled all of the lighting effects and Bluetooth connectivity, and another as a listener, which only set the colors that the other requested. These two Arduino sketches are available here.

I created the companion app for Android with MIT App Inventor instead of learning my way around Android Studio. I regretted this decision the entire time I worked on the app. I have no interest in providing the APK or project files because that would involve logging into AI2 again.
