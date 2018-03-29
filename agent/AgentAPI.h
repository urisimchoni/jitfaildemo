#include <jni.h>

#ifndef AgentAPI_H
#define AgentAPI_H
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_MyAgent_analyzeObj
(JNIEnv *, jclass, jobject);

#ifdef __cplusplus
}
#endif
#endif
