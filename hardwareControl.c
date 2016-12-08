
#include <stdio.h>
#include <stdlib.h>
#include <jni.h>	// /usr/lib/jvm/java-1.8.0-openjdk-amd64/include/jni.h

#include <android/log.h>	/* liblog */

jint c_ledOpen(JNIEnv *env, jobject cls);
void c_ledClose(JNIEnv *env, jobject cls);
jint c_ledCtrl(JNIEnv *env, jobject cls, jint whichLed, jint ledStatus);

#if 0
typedef struct {
	char *name;			// function name in Java
	char *signature;	// JNI description to describe the the type and number of parameters
	void *fnPtr;		// local function pointer in C
} JNINativeMethod;
#endif

static const JNINativeMethod methods[] = {
	{ "ledOpen", "()I", (void *)c_ledOpen },	// () means no parameter, V means return type void
	{ "ledClose", "()V", (void *)c_ledClose }, // () means no parameter, V means return type void
	{ "ledCtrl", "(II)I", (void *)c_ledCtrl }, // () means no parameter, V means return type void
};

JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *jvm, void *reserved)
{
	JNIEnv *env;
	jclass cls;
	
	if ((*jvm)->GetEnv(jvm, (void **)&env, JNI_VERSION_1_4)) {
		return JNI_ERR; /* JNI version not supported */
	}
	
	cls = (*env)->FindClass(env, "com/young/hardwareLibary/HardwareControl");
	if (cls == NULL) {
		return JNI_ERR;
	}
	
	/* 2. Mapping java method hello() to c function c_hello() */
	if ((*env)->RegisterNatives(env, cls, methods, sizeof(methods)/sizeof(methods[0])) < 0)
		return JNI_ERR;
	
	return JNI_VERSION_1_4;
}

jint c_ledOpen(JNIEnv *env, jobject cls)
{
	__android_log_print(ANDROID_LOG_DEBUG, "LEDDemo", "native c_ledOpen ...");
	return 0;
}

void c_ledClose(JNIEnv *env, jobject cls)
{
	__android_log_print(ANDROID_LOG_DEBUG, "LEDDemo", "native c_ledClose ...");
}

jint c_ledCtrl(JNIEnv *env, jobject cls, jint whichLed, jint ledStatus)
{
	__android_log_print(ANDROID_LOG_DEBUG, "LEDDemo", "native c_ledCtrl : %d, %d", whichLed, ledStatus);
	return 0;
}

