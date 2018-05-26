#include <algorithm>
#include <iostream>
#include <cstring>
#include <math.h>
#include <sstream>
#include <string>
#include <vector>

#include "real.h"
#include "fasttext.h"

#ifdef __cplusplus
#define EXTERN_C       extern "C"
#define EXTERN_C_BEGIN extern "C" {
#define EXTERN_C_END   }
#else
#define EXTERN_C       /* Nothing */
#define EXTERN_C_BEGIN /* Nothing */
#define EXTERN_C_END   /* Nothing */
#endif

EXTERN_C_BEGIN
fasttext::FastText* create(const char* model_name) {
  fasttext::FastText* new_fasttext = new fasttext::Fasttext();
  new_fasttext->loadModel(std::string(model_name));

  return new_fasttext;
}

void destroy(fasttext::FastText* destroy_fasttext) {
  delete destroy_fasttext;
}

void predict_string_free(const char* match) {
  if (match != NULL) {
    delete[] match;
  }
}

const char* predict(fasttext::FastText* fasttext_pointer, const char* key, int32_t number_of_predictions) {
  std::string string_key(key);
  std::stringstream key_stream;
  std::ostringstream output_stream;
  key_stream.str(string_key);
  key_stream << std::endl;

  std::vector<std::pair<real, std::string>> predictions;
  fasttext_pointer->predict(key_stream, number_of_predictions, predictions);

  for (auto iter = predictions.begin(); iter != predictions.end(); iter++) {
    output_stream << iter->second << " " << std::exp(iter->first) << " ";
  }

  if (!output_stream.str().empty()) {
    std::string first = output_stream.str();
    char *val  = new char[first.size() + 1]{0};
    val[first.size()] = '\0';
    memcpy(val, first.c_str(), first.size());

    return val;
  }

  return NULL;
}

EXTERN_C_END