////////////////////////////////////////////////////////////////////////////////
// Authors: superman@<unknown host>
// Description: AudioStimulusTask implementation
////////////////////////////////////////////////////////////////////////////////

#include "AudioStimulusTask.h"
#include "BCIStream.h"

RegisterFilter( AudioStimulusTask, 3 );
     // Change the location if appropriate, to determine where your filter gets
     // sorted into the chain. By convention:
     //  - filter locations within SignalSource modules begin with "1."
     //  - filter locations within SignalProcessing modules begin with "2."
     //       (NB: SignalProcessing modules must specify this with a Filter() command in their PipeDefinition.cpp file too)
     //  - filter locations within Application modules begin with "3."


AudioStimulusTask::AudioStimulusTask() :
  mrDisplay( Window() )
{
  // C++ does not initialize simple types such as numbers, or pointers, by default.
  // Rather, they will have random values.
  // Take care to initialize any member variables here, so they have predictable values
  // when used for the first time.
}

AudioStimulusTask::~AudioStimulusTask()
{
  Halt();
  // If you have allocated any memory with malloc(), call free() here.
  // If you have allocated any memory with new[], call delete[] here.
  // If you have created any object using new, call delete here.
  // Either kind of deallocation will silently ignore null pointers, so all
  // you need to do is to initialize those to zero in the constructor, and
  // deallocate them here.
}

void
AudioStimulusTask::Publish()
{
  // Define any parameters that the filter needs....

 BEGIN_PARAMETER_DEFINITIONS

   "Application:AudioStimulusTask int EnableAudioStimulusTask= 0 0 0 1 // enable AudioStimulusTask? (boolean)",                       // These are just examples:
   "Application:AudioStimulusTask float SomeParameter=  0.0 0.0 -1.0 1.0 // a useless AudioStimulusTask parameter",   //  change them, or remove them.

 END_PARAMETER_DEFINITIONS


  // ...and likewise any state variables:

 BEGIN_STATE_DEFINITIONS

   "SomeState       8 0 0 0",    // These are just examples. Change them, or remove them.
   "SomeOtherState 16 0 0 0",

 END_STATE_DEFINITIONS

}

void
AudioStimulusTask::Preflight( const SignalProperties& Input, SignalProperties& Output ) const
{
  // The user has pressed "Set Config" and we need to sanity-check everything.
  // For example, check that all necessary parameters and states are accessible:
  //
  // Parameter( "Milk" );
  // State( "Bananas" );
  //
  // Also check that the values of any parameters are sane:
  //
  // if( (float)Parameter( "Denominator" ) == 0.0f )
  //      bcierr << "Denominator cannot be zero";
  //
  // Errors issued in this way, during Preflight, still allow the user to open
  // the Config dialog box, fix bad parameters and re-try.  By contrast, errors
  // and C++ exceptions at any other stage (outside Preflight) will make the
  // system stop, such that BCI2000 will need to be relaunched entirely.

  // Note that the AudioStimulusTask instance itself, and its members, are read-only during
  // this phase, due to the "const" at the end of the Preflight prototype above.
  // Any methods called by Preflight must also be "const" in the same way.

  Output = Input; // this simply passes information through about SampleBlock dimensions, etc....

}


void
AudioStimulusTask::Initialize( const SignalProperties& Input, const SignalProperties& Output )
{
  // The user has pressed "Set Config" and all Preflight checks have passed.
  // The signal properties can no longer be modified, but the const limitation has gone, so
  // the AudioStimulusTask instance itself can be modified. Allocate any memory you need, start any
  // threads, store any information you need in private member variables.
}

void
AudioStimulusTask::StartRun()
{
  // The user has just pressed "Start" (or "Resume")
  bciout << "Hello World!";
}


void
AudioStimulusTask::Process( const GenericSignal& Input, GenericSignal& Output )
{

  // And now we're processing a single SampleBlock of data.
  // Remember not to take too much CPU time here, or you will break the real-time constraint.

  Output = Input; // This passes the signal through unmodified.
}

void
AudioStimulusTask::StopRun()
{
  // The Running state has been set to 0, either because the user has pressed "Suspend",
  // or because the run has reached its natural end.
  bciwarn << "Goodbye World.";
  // You know, you can delete methods if you're not using them.
  // Remove the corresponding declaration from AudioStimulusTask.h too, if so.
}

void
AudioStimulusTask::Halt()
{
  // Stop any threads or other asynchronous activity.
  // Good practice is to write the Halt() method such that it is safe to call it even *before*
  // Initialize, and safe to call it twice (e.g. make sure you do not delete [] pointers that
  // have already been deleted:  set them to NULL after deletion).
}

