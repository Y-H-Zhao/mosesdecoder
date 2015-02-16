#pragma once

#include <string>
#include "VWFeatureSource.h"

namespace Moses
{

class VWFeatureSourceBagOfWords : public VWFeatureSource
{
public:
  VWFeatureSourceBagOfWords(const std::string &line)
    : VWFeatureSource(line) {
    ReadParameters();

    // Call this last
    VWFeatureBase::UpdateRegister();
  }

  void operator()(const InputType &input
                  , const InputPath &inputPath
                  , const WordsRange &sourceRange
                  , Discriminative::Classifier &classifier) const {
    for (size_t i = 1; i < input.GetSize(); i++) {
      classifier.AddLabelIndependentFeature("bigram^" + GetWord(input, i - 1) + "^" + GetWord(input, i));
    }
  }

  virtual void SetParameter(const std::string& key, const std::string& value) {
    VWFeatureSource::SetParameter(key, value);
  }
};

}
