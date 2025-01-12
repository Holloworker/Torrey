#include "Shape.h"
#include "transform.h"



Vector4 GetNormalByHitPoint(Vector3 hitpoint, ParsedSphere& sphere)
{
	Vector4 normal_original = Vector4(hitpoint / sphere.radius, 0.);
	return normal_original;
}
Vector4 GetNormalByHitPoint(Vector3 hitpoint, Triangle& triangle)
{

	Vector3 p1 = triangle.mesh->positions[triangle.mesh->indices[triangle.index][0]];
	Vector3 p2 = triangle.mesh->positions[triangle.mesh->indices[triangle.index][1]];
	Vector3 p3 = triangle.mesh->positions[triangle.mesh->indices[triangle.index][2]];
	Vector3 normal = normalize(cross((p2 - p1), (p3 - p1)));
	normal = normalize(normal);
	return Vector4(normal, 0.);
}

Vector4 GetNormalByHitPoint_Smooth(Vector3 hitpoint, Triangle& triangle)
{
	Vector3 p1 = triangle.mesh->positions[triangle.mesh->indices[triangle.index][0]];
	Vector3 p2 = triangle.mesh->positions[triangle.mesh->indices[triangle.index][1]];
	Vector3 p3 = triangle.mesh->positions[triangle.mesh->indices[triangle.index][2]];
	Vector3 orig = Vector3(0.1, 0.1, 0.1);
	Vector3 direct = normalize(hitpoint - orig);
	Real b1 = dot(cross(direct, p3 - p1), orig - p1) /
		dot(cross(direct, p3 - p1), p2 - p1);

	Real b2 = dot(cross(orig - p1, p2 - p1), direct) /
		dot(cross(direct, p3 - p1), p2 - p1);
	Vector3 barycentric = Vector3(1 - b1 - b2, b1, b2);

	Vector3 normal_1 = triangle.mesh->normals[triangle.mesh->indices[triangle.index][0]];
	Vector3 normal_2 = triangle.mesh->normals[triangle.mesh->indices[triangle.index][1]];
	Vector3 normal_3 = triangle.mesh->normals[triangle.mesh->indices[triangle.index][2]];
	Vector3 normal_p = normalize(barycentric.x * normal_1 + barycentric.y * normal_2 + barycentric.z * normal_3);
	return Vector4(normal_p, 0.);
}

Real GetAreaByShape(ParsedSphere& sphere)
{
	return c_PI * sphere.radius * sphere.radius;
}
Real GetAreaByShape(Triangle& triangle)
{
	Vector3 p1 = triangle.mesh->positions[triangle.mesh->indices[triangle.index][0]];
	Vector3 p2 = triangle.mesh->positions[triangle.mesh->indices[triangle.index][1]];
	Vector3 p3 = triangle.mesh->positions[triangle.mesh->indices[triangle.index][2]];
	Vector3 normal = cross((p2 - p1), (p3 - p1));

	return length(normal) / 2.;
}
Color ParsedColorToColor(ParsedColor& parsed_color)
{
	if(parsed_color.index() == 0) // RGB color
	{
		return Color{ std::get<Vector3>(parsed_color) };
	}
	else // Texture
	{
		return Color{ Texture(std::get<ParsedImageTexture>(parsed_color)) };
	}
}

Scene ParsedSceneToScene(ParsedScene& parsed_scene)
{
	std::vector<Shape> shapes;
	std::vector<Material> materials;
	std::vector<ParsedShape*> src_shapes;
	for (ParsedShape& shape : parsed_scene.shapes)
	{
		if (shape.index() == 0) // sphere
			shapes.push_back(Shape{ std::get<ParsedSphere>(shape) });
		else // trianglemesh
		{
			ParsedTriangleMesh& mesh = std::get<ParsedTriangleMesh>(shape);
			for (int i = 0; i < mesh.indices.size(); i++)
			{
				shapes.push_back(Shape{ Triangle{&mesh, i, mesh.area_light_id} });
			}
		}
		src_shapes.push_back(&shape);
	}

	for (ParsedMaterial& material : parsed_scene.materials)
	{
		if (material.index() == 0) // Diffuse
		{
			ParsedDiffuse& p_d = std::get<ParsedDiffuse>(material);
			Diffuse m_d = { ParsedColorToColor(p_d.reflectance) };
			materials.push_back(Material{ m_d });
		}
		else if(material.index() == 1) // Mirror	
		{
			ParsedMirror& p_mir = std::get<ParsedMirror>(material);
			Mirror m_mir = { ParsedColorToColor(p_mir.reflectance) };
			materials.push_back(Material{ m_mir });
		}
		else if(material.index() == 2) // Plastic
		{
			ParsedPlastic& p_plas = std::get<ParsedPlastic>(material);
			Plastic m_plas = { p_plas.eta,ParsedColorToColor(p_plas.reflectance) };
			materials.push_back(Material{ m_plas });
		}
		else if(material.index() == 3) // Phong
		{
			ParsedPhong& p_pho = std::get<ParsedPhong>(material);
			Phong m_pho = {ParsedColorToColor(p_pho.reflectance),  p_pho.exponent};
			materials.push_back(Material{ m_pho });
		}
		else if(material.index() == 4) // BlinnPhong
		{
			ParsedBlinnPhong& p_blpho = std::get<ParsedBlinnPhong>(material);
			BlinnPhong m_blpho = { ParsedColorToColor(p_blpho.reflectance),  p_blpho.exponent };
			materials.push_back(Material{ m_blpho });
		}
		else if(material.index() == 5) // BlinnPhongMicrofacet
		{
			ParsedBlinnPhongMicrofacet& p_blphomic = std::get<ParsedBlinnPhongMicrofacet>(material);
			BlinnPhongMicrofacet m_blphomic = { ParsedColorToColor(p_blphomic.reflectance),  p_blphomic.exponent };
			materials.push_back(Material{ m_blphomic });
		}
		else if (material.index() == 6) // Glass
		{
			ParsedGlass& p_glass = std::get<ParsedGlass>(material);
			Glass m_glass = { p_glass.eta, ParsedColorToColor(p_glass.reflectance) };
			materials.push_back(Material{ m_glass });
		}
		else if (material.index() == 7) // Volume
		{
			ParsedVolume& p_volume = std::get<ParsedVolume>(material);
			Volume m_volume = { p_volume.thickness, ParsedColorToColor(p_volume.reflectance) };
			materials.push_back(Material{ m_volume });
		}
	}
	return Scene{ parsed_scene.camera,
	materials,
	parsed_scene.lights,
	shapes,
		src_shapes,
	parsed_scene.background_color,
	parsed_scene.samples_per_pixel };
}

