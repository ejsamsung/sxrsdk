/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
#include <stdlib.h>
/* Header for class jassimp_Jassimp */

#ifndef _Included_jassimp_Jassimp
#define _Included_jassimp_Jassimp
#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT jint JNICALL Java_com_samsungxr_jassimp_Jassimp_getVKeysize
  (JNIEnv *, jclass);
JNIEXPORT jint JNICALL Java_com_samsungxr_jassimp_Jassimp_getQKeysize
  (JNIEnv *, jclass);
JNIEXPORT jint JNICALL Java_com_samsungxr_jassimp_Jassimp_getV3Dsize
  (JNIEnv *, jclass);
JNIEXPORT jint JNICALL Java_com_samsungxr_jassimp_Jassimp_getfloatsize
  (JNIEnv *, jclass);
JNIEXPORT jint JNICALL Java_com_samsungxr_jassimp_Jassimp_getintsize
  (JNIEnv *, jclass);
JNIEXPORT jint JNICALL Java_com_samsungxr_jassimp_Jassimp_getuintsize
  (JNIEnv *, jclass);
JNIEXPORT jint JNICALL Java_com_samsungxr_jassimp_Jassimp_getdoublesize
  (JNIEnv *, jclass);
JNIEXPORT jint JNICALL Java_com_samsungxr_jassimp_Jassimp_getlongsize
  (JNIEnv *, jclass);

/*
 * Class:     jassimp_Jassimp
 * Method:    getErrorString
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_samsungxr_jassimp_Jassimp_getErrorString
  (JNIEnv *, jclass);

/*
 * Class:     jassimp_Jassimp
 * Method:    aiImportFile
 * Signature: (Ljava/lang/String;J)Ljassimp/AiScene;
 */
JNIEXPORT jobject JNICALL Java_com_samsungxr_jassimp_Jassimp_aiImportFile
  (JNIEnv *, jclass, jstring, jlong, jobject, jobject);

#ifdef __cplusplus
}
#endif
#endif
