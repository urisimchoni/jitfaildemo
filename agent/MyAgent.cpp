#include "AgentAPI.h"
#include "jvmti.h"

static jvmtiEnv *jvmti;

JNIEXPORT void JNICALL Java_MyAgent_analyzeObj(JNIEnv *jni_env, jclass, jobject obj)
{
	jclass klass = jni_env->GetObjectClass(obj);
	jfieldID* klassFields;
	jint fieldCount;
	jvmtiError err = jvmti->GetClassFields(klass, &fieldCount, &klassFields);
	if (err != JVMTI_ERROR_NONE) {
		printf("%s\tfailed to get class fields: %d\n", __FUNCTION__, err);
		return;
	}

	for (int i = 0; i < fieldCount; ++i) {
		static int num_watched;
		printf("%d watched fields\n", ++num_watched);
		err = jvmti->SetFieldAccessWatch(klass, klassFields[i]);
		if (err != JVMTI_ERROR_NONE && err != JVMTI_ERROR_DUPLICATE) {
			printf("%s\tfailed to set field access: %d\n", __FUNCTION__, err);
			return;
		}
	}

	jvmti->Deallocate((unsigned char*)klassFields);
}

static void JNICALL onFieldModified(jvmtiEnv *jvmti_env,
	JNIEnv* jni_env,
	jthread thread,
	jmethodID method,
	jlocation location,
	jclass field_klass,
	jobject parentObject,
	jfieldID field,
	char signature_type,
	jvalue new_value)
{
}

static void JNICALL onFieldAccess(jvmtiEnv *jvmti_env,
	JNIEnv* jni_env,
	jthread thread,
	jmethodID method,
	jlocation location,
	jclass field_klass,
	jobject parentObject,
	jfieldID field)
{
}

static void onObjectFree(jvmtiEnv *jvmti_env, jlong tag)
{
}

static void onClassPrepare(jvmtiEnv *jvmti_env,
	JNIEnv* jni_env,
	jthread,
	jclass klass)
{
}

JNIEXPORT jint JNICALL Agent_OnLoad(JavaVM *jvm, char *options, void *reserved)
{
	jvmtiEventCallbacks callbacks = {};
	jvmtiError error;

	jint result = jvm->GetEnv((void **)&jvmti, JVMTI_VERSION_1_1);
	if (result != JNI_OK) {
		printf("%s\tUnable to access JVMTI!: %d\n", __FUNCTION__, result);
	} else {
		printf("Agent succesfully loaded\n");
	}

	jvmtiCapabilities capa = {};

	capa.can_generate_field_modification_events = 1;
	capa.can_generate_field_access_events = 1;
	capa.can_tag_objects = 1;
	capa.can_get_bytecodes = 1;
	capa.can_generate_object_free_events = 1;
	error = jvmti->AddCapabilities(&capa);
	if (error != JVMTI_ERROR_NONE) {
		printf("%s\tfailed to set capabilities: %d\n", __FUNCTION__, error);
	}

	callbacks.FieldModification = &onFieldModified;
	callbacks.FieldAccess = &onFieldAccess;
	callbacks.ObjectFree = &onObjectFree;
	callbacks.ClassPrepare = &onClassPrepare;

	error = jvmti->SetEventCallbacks(&callbacks, sizeof(callbacks));
	if (error != JVMTI_ERROR_NONE) {
		printf("%s\tfailed to set event callbacks: %d\n", __FUNCTION__, error);
	}

	error = jvmti->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_OBJECT_FREE, nullptr);
	if (error != JVMTI_ERROR_NONE) {
		printf("%s\tfailed to set object free notifications: %d\n", __FUNCTION__, error);
	}

	return JNI_OK;
}

