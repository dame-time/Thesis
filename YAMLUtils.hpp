//
//  YAMLUtils.h
//  Thesis
//
//  Created by Davide Paollilo on 10/04/23.
//

#ifndef YAMLUtils_h
#define YAMLUtils_h

#include <yaml-cpp/yaml.h>

void YAMLSerializeVector3(YAML::Emitter& out, const Math::Vector3& vector) {
    out << YAML::BeginMap;
    out << YAML::Key << "X" << YAML::Value << vector.coordinates.x;
    out << YAML::Key << "Y" << YAML::Value << vector.coordinates.y;
    out << YAML::Key << "Z" << YAML::Value << vector.coordinates.z;
    out << YAML::EndMap;
}

void YAMLSerializeVector4(YAML::Emitter& out, const Math::Vector4& vector) {
    out << YAML::BeginMap;
    out << YAML::Key << "X" << YAML::Value << vector.coordinates.x;
    out << YAML::Key << "Y" << YAML::Value << vector.coordinates.y;
    out << YAML::Key << "Z" << YAML::Value << vector.coordinates.z;
    out << YAML::Key << "W" << YAML::Value << vector.coordinates.w;
    out << YAML::EndMap;
}

void YAMLSerializeMatrix4(YAML::Emitter& out, const Math::Matrix4& matrix) {
    out << YAML::BeginMap;
    out << YAML::Key << "0" << YAML::Value << matrix.data[0];
    out << YAML::Key << "1" << YAML::Value << matrix.data[1];
    out << YAML::Key << "2" << YAML::Value << matrix.data[2];
    out << YAML::Key << "3" << YAML::Value << matrix.data[3];
    out << YAML::Key << "4" << YAML::Value << matrix.data[4];
    out << YAML::Key << "5" << YAML::Value << matrix.data[5];
    out << YAML::Key << "6" << YAML::Value << matrix.data[6];
    out << YAML::Key << "7" << YAML::Value << matrix.data[7];
    out << YAML::Key << "8" << YAML::Value << matrix.data[8];
    out << YAML::Key << "9" << YAML::Value << matrix.data[9];
    out << YAML::Key << "10" << YAML::Value << matrix.data[10];
    out << YAML::Key << "11" << YAML::Value << matrix.data[11];
    out << YAML::Key << "12" << YAML::Value << matrix.data[12];
    out << YAML::Key << "13" << YAML::Value << matrix.data[13];
    out << YAML::Key << "14" << YAML::Value << matrix.data[14];
    out << YAML::Key << "15" << YAML::Value << matrix.data[15];
    out << YAML::EndMap;
}

void YAMLSerializeQuadric(YAML::Emitter& out, SM::Quadric& q) {
    out << YAML::BeginMap;
    out << YAML::Key << "A" << YAML::Value;
    YAMLSerializeMatrix4(out, q.getA());
    out << YAML::Key << "b" << YAML::Value;
    YAMLSerializeVector4(out, q.getB());
    out << YAML::Key << "c" << YAML::Value << q.getC();
    out << YAML::EndMap;
}

#endif /* YAMLUtils_h */
