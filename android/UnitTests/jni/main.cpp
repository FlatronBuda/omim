// @todo(VB) this file should be generated with a script based on tests_list.sh
#include "mock.hpp"

#include "integration_tests/jni/test.hpp"
#include "indexer/indexer_tests/jni/test.hpp"

#include <android_native_app_glue.h>


void android_main(struct android_app * state) 
{
  // Make sure glue isn't stripped.
  app_dummy();
  
  integration_tests::test(state);
  indexer_tests::test(state);

  // @todo(VB) you need to write code to leave the activity correctly after all tests are finished. And show a dialog with the results.
  // @todo(VB) It's nice to show the result of the test on Android screen. Message box or something like that.
}
