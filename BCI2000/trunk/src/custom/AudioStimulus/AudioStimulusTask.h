////////////////////////////////////////////////////////////////////////////////
// Authors: superman@<unknown host>
// Description: AudioStimulusTask header
////////////////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_AUDIOSTIMULUSTASK_H  // makes sure this header is not included more than once
#define INCLUDED_AUDIOSTIMULUSTASK_H

#include "ApplicationBase.h"

class AudioStimulusTask : public ApplicationBase
{
 public:
  AudioStimulusTask();
  ~AudioStimulusTask();
  void Publish() override;
  void Preflight( const SignalProperties& Input, SignalProperties& Output ) const override;
  void Initialize( const SignalProperties& Input, const SignalProperties& Output ) override;
  void StartRun() override;
  void Process( const GenericSignal& Input, GenericSignal& Output ) override;
  void StopRun() override;
  void Halt() override;

 private:
   ApplicationWindow& mrDisplay;
   // Use this space to declare any AudioStimulusTask-specific methods and member variables you'll need
};

#endif // INCLUDED_AUDIOSTIMULUSTASK_H
