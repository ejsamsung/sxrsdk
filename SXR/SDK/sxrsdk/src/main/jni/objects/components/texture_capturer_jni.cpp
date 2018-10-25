/***************************************************************************
 * JNI
 ***************************************************************************/

#include "objects/components/texture_capturer.h"
#include "shaders/shader_manager.h"
#include "util/sxr_jni.h"
#include "util/sxr_log.h"
#include "glm/gtc/type_ptr.hpp"

namespace sxr {
extern "C" {
JNIEXPORT jlong JNICALL
Java_com_samsungxr_NativeTextureCapturer_ctor(JNIEnv * env,
        jobject obj, jlong shaderManagerPtr);

JNIEXPORT jlong JNICALL
Java_com_samsungxr_NativeTextureCapturer_getComponentType(JNIEnv * env, jobject obj);

JNIEXPORT void JNICALL
Java_com_samsungxr_NativeTextureCapturer_setCapturerObject(JNIEnv * env, jobject obj,
        jlong ptr, jobject capturerObject);

JNIEXPORT void JNICALL
Java_com_samsungxr_NativeTextureCapturer_setRenderTexture(JNIEnv * env, jobject obj,
        jlong ptr, jlong ptrRenderTexture);

JNIEXPORT void JNICALL
Java_com_samsungxr_NativeTextureCapturer_setCapture(JNIEnv * env, jobject obj,
        jlong ptr, jboolean capture, jfloat fps);

void
Java_com_samsungxr_NativeTextureCapturer_callbackFromNative(
        JNIEnv * env, jobject obj, jint index, char *info);
}
;

static jmethodID sCallbackMethod;

JNIEXPORT jlong JNICALL
Java_com_samsungxr_NativeTextureCapturer_ctor(JNIEnv * env,
        jobject obj, jlong shaderManagerPtr) {

    return reinterpret_cast<jlong>(new TextureCapturer(
            reinterpret_cast<ShaderManager*>(shaderManagerPtr)));
}

JNIEXPORT jlong JNICALL
Java_com_samsungxr_NativeTextureCapturer_getComponentType(JNIEnv * env, jobject obj) {
    return TextureCapturer::getComponentType();
}

JNIEXPORT void JNICALL
Java_com_samsungxr_NativeTextureCapturer_setCapturerObject(JNIEnv * env, jobject obj,
        jlong ptr, jobject capturerObject) {
    TextureCapturer *capturer = reinterpret_cast<TextureCapturer*>(ptr);
    capturer->setCapturerObject(env, capturerObject);
}

JNIEXPORT void JNICALL
Java_com_samsungxr_NativeTextureCapturer_setRenderTexture(JNIEnv * env, jobject obj,
        jlong ptr, jlong ptrRenderTexture) {
    TextureCapturer *capturer = reinterpret_cast<TextureCapturer*>(ptr);
    capturer->setRenderTexture(reinterpret_cast<RenderTexture*>(ptrRenderTexture));
}

JNIEXPORT void JNICALL
Java_com_samsungxr_NativeTextureCapturer_setCapture(JNIEnv * env, jobject obj,
        jlong ptr, jboolean capture, jfloat fps) {
    TextureCapturer *capturer = reinterpret_cast<TextureCapturer*>(ptr);
    capturer->setCapture(capture, fps);
}

void
Java_com_samsungxr_NativeTextureCapturer_callbackFromNative(JNIEnv * env,
        jobject obj, jint msg, char *info) {

    // Initialize method id
    if (!sCallbackMethod) {
        jclass clz = env->GetObjectClass(obj);
        sCallbackMethod = env->GetMethodID(clz,
                "callbackFromNative", "(ILjava/lang/String;)V");
    }

    jstring strInfo = info ? env->NewStringUTF(info) : 0;
    env->CallVoidMethod(obj, sCallbackMethod, msg, strInfo);
}

}
