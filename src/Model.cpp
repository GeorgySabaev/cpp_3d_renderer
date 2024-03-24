#include "Model.hpp"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include <iostream>

namespace cpp_renderer {
Model::Model(std::string path) {
  tinyobj::ObjReader reader;
  tinyobj::ObjReaderConfig reader_config;
  reader_config.mtl_search_path = "./";
  if (!reader.ParseFromFile(path, reader_config)) {
    if (!reader.Error().empty()) {
      std::cerr << "TinyObjReader: " << reader.Error();
    }
    exit(1);
  }

  auto &attrib = reader.GetAttrib();
  auto &shapes = reader.GetShapes();
  auto &materials = reader.GetMaterials();

  if (shapes.size() != 1) {
    std::cerr << "Model could not be loaded: " << path
              << ". Only one shape models are supported." << std::endl;
    exit(1);
  }

  auto &mesh = shapes[0].mesh;
  auto poly_count = mesh.num_face_vertices.size();
  std::cout << "poly_count " << poly_count << std::endl;
  std::cout << "mesh.indices.size() " << mesh.indices.size() << std::endl;
  polygons.reserve(poly_count);
  for (size_t face_i = 0; face_i < poly_count; ++face_i) {
    assert(mesh.num_face_vertices[face_i] == 3);
    Triangle polygon;
    for (size_t vert_i = 0; vert_i < 3; ++vert_i) {
      size_t offset = face_i * 3 + vert_i;
      polygon[vert_i] = Triangle::Vector3{
          attrib.vertices[mesh.indices[offset].vertex_index * 3],
          attrib.vertices[mesh.indices[offset].vertex_index * 3 + 1],
          attrib.vertices[mesh.indices[offset].vertex_index * 3 + 2]};
    }
    polygons.push_back(polygon);
  }
}

} // namespace cpp_renderer
