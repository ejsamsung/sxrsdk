/* Copyright 2015 Samsung Electronics Co., LTD
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


/***************************************************************************
 * JNI
 ***************************************************************************/

#include <engine/renderer/renderer.h>
#include "vulkan/vulkan_headers.h"

namespace sxr {
extern "C" {

    JNIEXPORT jlong JNICALL
        Java_com_samsungxr_NativeVulkanCore_getInstance(JNIEnv* env, jobject obj, jobject surface, jint vulkanPropValue);

    JNIEXPORT jint JNICALL
        Java_com_samsungxr_NativeVulkanCore_getSwapChainIndexToRender(JNIEnv* env, jobject obj);

    JNIEXPORT void JNICALL
        Java_com_samsungxr_NativeVulkanCore_resetTheInstance(JNIEnv* env, jobject obj);

    JNIEXPORT void JNICALL
        Java_com_samsungxr_NativeVulkanCore_recreateSwapchain(JNIEnv* env, jobject obj, jobject surface);

    JNIEXPORT int JNICALL
        Java_com_samsungxr_NativeVulkanCore_getVulkanPropValue(JNIEnv* env, jobject obj);

    JNIEXPORT bool JNICALL
        Java_com_samsungxr_NativeVulkanCore_isInstancePresent(JNIEnv* env, jobject obj);
    };

    JNIEXPORT jlong JNICALL
    Java_com_samsungxr_NativeVulkanCore_getInstance(JNIEnv * env, jobject obj, jobject surface, jint vulkanPropValue){
        ANativeWindow * newNativeWindow = ANativeWindow_fromSurface(env, surface);
        VulkanCore * vulkanCore = VulkanCore::getInstance(newNativeWindow, vulkanPropValue);
        return (reinterpret_cast<jlong>(vulkanCore));
    }

    JNIEXPORT jint JNICALL
    Java_com_samsungxr_NativeVulkanCore_getSwapChainIndexToRender(JNIEnv * env, jobject obj){
        VulkanCore * vulkanCore = VulkanCore::getInstance();
        return vulkanCore->getSwapChainIndexToRender();
    }

    JNIEXPORT void JNICALL
    Java_com_samsungxr_NativeVulkanCore_resetTheInstance(JNIEnv * env, jobject obj){
        VulkanCore * vulkanCore = VulkanCore::getInstance();
        return vulkanCore->releaseInstance();
    }

    JNIEXPORT void JNICALL
    Java_com_samsungxr_NativeVulkanCore_recreateSwapchain(JNIEnv * env, jobject obj, jobject surface){
        ANativeWindow * newNativeWindow = ANativeWindow_fromSurface(env, surface);
        VulkanCore * vulkanCore = VulkanCore::getInstance();
        return vulkanCore->recreateSwapChain(newNativeWindow);
    }

    JNIEXPORT int JNICALL
    Java_com_samsungxr_NativeVulkanCore_getVulkanPropValue(JNIEnv * env, jobject obj){
        return Renderer::getVulkanPropValue();
    }

    JNIEXPORT bool JNICALL
    Java_com_samsungxr_NativeVulkanCore_isInstancePresent(JNIEnv* env, jobject obj){
        return VulkanCore::isInstancePresent();
    }
}