#include "main_tool.h"

std::ostream &operator<< (std::ostream &out, const glm::vec2 &vec) {
    out << "{" << vec.x << " " << vec.y << "}";
    return out;
}
std::ostream &operator<< (std::ostream &out, const glm::vec3 &vec) {
    out << "{" << vec.x << " " << vec.y << " "<< vec.z<< "}";
    return out;
}
std::ostream &operator<< (std::ostream &out, const glm::vec4 &vec) {
    out << "{" << vec.x << " " << vec.y << " "<< vec.z<< " " << vec.w << "}";
    return out;
}
std::ostream &operator<< (std::ostream &out, const glm::mat4 &mat) {
     out << '}';
    for(int i=0; i< mat.length(); i++) {
        out << "{" << mat[i].x << " " << mat[i].y << " "<< mat[i].z<< " " << mat[i].w << "}" << std::endl;
    }
     out << '{';
}

void vecInArray(std::vector<float> &array, glm::vec2 value) {
    array.push_back(value.x);
    array.push_back(value.y);
}
void vecInArray(std::vector<float> &array, glm::vec3 value) {
    array.push_back(value.x);
    array.push_back(value.y);
    array.push_back(value.z);
}
void vecInArray(std::vector<float> &array, glm::vec4 value) {
    array.push_back(value.x);
    array.push_back(value.y);
    array.push_back(value.z);
    array.push_back(value.w);
}
