# Thai Speech Envelope Auditory Attention Detection Using EEG Decoding
## Document Control
| version | author             | date         | reason          |
|---------|--------------------|--------------|-----------------|
| 1       | Shalong Samretngan | Dec 19, 2024 | initial document|


This is developement evironment that is the partial fulfillment of the requirements for the Degree of Master of Engineering in Computer Engineering, Faculty of Engineering, Chulalongkorn University. Academic year 2023.

---
## Setup BCI2000
With the [BCI2000 Wiki Quickstart](https://www.bci2000.org/mediawiki/index.php/Programming_Howto:Quickstart_Guide), the setup `NewBCI2000Module`, `NewBCI2000Filter` and `NewBCI2000FilterTool` will be necessary before create custom module.

1. Go to path and install (`qt` is required; `brew install qt@6`)
    ```bash
    cd ./BCI2000/trunk
    ./install
    ```
    Enter the information
    ```bash
    Please drag and drop your Qt folder, then press ENTER: /usr/local/opt/qt@6
    ```

---

## Guide to Creating a Custom BCI2000 Module for Sound Stimuli and EEG Recording
Generate by `ChatGPT` model `GPT-4o`

This guide explains how to create a **custom BCI2000 module** that:
1. Randomizes and plays speech sound files to the **right/left audio channels**.
2. Presents the sound as stimuli.
3. Records EEG signals using **gMOBIlabPlus** (via `gMOBIlabPlus.dll`).
4. Marks signals to indicate stimulus presentation and EEG recording.

### Step 1: Project Setup
1. **Navigate to the build directory**:
   ```bash
   cd ./BCI2000/trunk/build
   ```

2. **Run `NewBCI2000Module` to create a new Application module**:
   - Launch the module template generator:
     ```bash
     ./NewBCI2000Module
     ```
   - Answer the prompts:
     1. **Type of module**: Enter `3` (Application module).
     2. **Module name**: Use a name like `AudioStimulus`.
     3. **Project directory**: Use the default `..\src\custom`.

3. **Run CMake** to integrate the new project:
   - Follow **Step 1** of the "Setup" section to regenerate the Visual Studio solution (`BCI2000.sln`).
   - Open the solution file in **Visual Studio**.


### Step 2: Implement Sound Stimulus Presentation
#### 1. Include Necessary Libraries
- Use the **Windows Multimedia API** for simple sound playback:
   - Add `<mmsystem.h>` to your project.
   - Link the required libraries in **Project Properties → Linker → Input → Additional Dependencies**.

#### 2. Randomize Sound File Selection
- Create arrays to hold **6 files each** for right and left audio channels:
   ```cpp
   const std::string rightFiles[6] = {
       "audio/right1.wav", "audio/right2.wav", "audio/right3.wav",
       "audio/right4.wav", "audio/right5.wav", "audio/right6.wav"
   };
   const std::string leftFiles[6] = {
       "audio/left1.wav", "audio/left2.wav", "audio/left3.wav",
       "audio/left4.wav", "audio/left5.wav", "audio/left6.wav"
   };
   ```

- Randomly select a file:
   ```cpp
   #include <cstdlib>
   int index = rand() % 6;  // Random number between 0-5
   std::string chosenFile = rightFiles[index];  // For right channel
   ```

#### 3. Play the Selected Sound File
- Use `PlaySound` to play the sound:
   ```cpp
   #include <mmsystem.h>
   PlaySound(chosenFile.c_str(), NULL, SND_FILENAME | SND_ASYNC);
   ```

#### 4. Manage Stimulus Timing
- Add delays to control stimulus presentation intervals:
   ```cpp
   Sleep(1000);  // Delay 1 second between stimuli
   ```


### Step 3: Record EEG Signal Using gMOBIlabPlus

#### 1. Integrate gMOBIlabPlus.dll
- Locate the `gMOBIlabPlus.dll` that supports BCI2000.
- Add the DLL path to your **project configuration**:
   - In Visual Studio:
     - Go to **Project Properties → Linker → Input → Additional Dependencies**.
     - Add the path to `gMOBIlabPlus.dll`.

#### 2. Mark EEG Signals with BCI2000 States
- Use **BCI2000 States** to mark events like stimulus onset and offset:
   ```cpp
   State("StimulusCode") = 1;  // Marker: Stimulus starts
   PlaySound(chosenFile.c_str(), NULL, SND_FILENAME | SND_ASYNC);
   State("StimulusCode") = 0;  // Marker: Stimulus ends
   ```

- Ensure that markers are logged in the EEG signal stream.


### Step 4: Compile and Test

1. **Rebuild the BCI2000 solution**:
   - Open the `BCI2000.sln` file in Visual Studio and build the solution.

2. **Test the Application Module**:
   - Run the module with the BCI2000 Operator using a batch file:
     ```cmd
     C:\BCI2000\3.x\batch\CursorTask_SignalGenerator.bat
     ```

3. **Verify EEG Signal**:
   - Use BCI2000’s **Offline Analysis Tool** to check:
     - **Stimulus markers** (`StimulusCode`) in the EEG data.
     - Synchronization between sound stimuli and EEG recording.

