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
 * Orthogonal camera for scene rendering.
 ***************************************************************************/

#include "objects/components/orthogonal_camera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace sxr {

glm::mat4 OrthogonalCamera::getProjectionMatrix() const {
    if(is_custom) {
        return projection_matrix_;
    }

    return glm::ortho(left_clipping_distance_, right_clipping_distance_,
            bottom_clipping_distance_, top_clipping_distance_,
            near_clipping_distance_, far_clipping_distance_);
}

void OrthogonalCamera::setProjectionMatrix(const glm::mat4& matrix) {
        projection_matrix_ = matrix;
        is_custom = true;
}


}
