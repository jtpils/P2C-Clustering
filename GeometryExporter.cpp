////////////////////////////////////////////////////////////////////////////////////
// Copyright © Charalambos "Charis" Poullis, charalambos@poullis.org    	  //
// This work can only be used under an exclusive license of the author.           //
////////////////////////////////////////////////////////////////////////////////////

#ifndef __GEOMETRY_EXPORTER_CPP__
#define __GEOMETRY_EXPORTER_CPP__

#include "GeometryExporter.h"

void GeometryExporter::exportToOBJ(const char *file_name, GeometricObject *object)	{
	FILE *file_ptr = fopen(_format("%s.obj",file_name).c_str(),"w");
	if (!file_ptr) return;


    time_t t = time(0);   // get time now
    struct tm *now = localtime(&t);
    std::string time_string = _format("%d - %d - %d", (now->tm_year + 1900) , (now->tm_mon + 1) , now->tm_mday);
	//go through the vertices and faces and export all
	fprintf(file_ptr,"###################################################\n");
	fprintf(file_ptr,"# Generated by P2C-Clustering                     #\n");
	fprintf(file_ptr,"# Copyright © Charalambos \"Charis\" Poullis      #\n");
	fprintf(file_ptr,"# http://www.poullis.org                          #\n");
	fprintf(file_ptr,"###################################################\n");
	fprintf(file_ptr,"# Created on %s\n",time_string.c_str());
	fprintf(file_ptr,"#\n\n");

	std::vector<Vector3f> vertices = object->getVertices();
	for (int i=0;i<vertices.size();i++)		{
		Vector3f vertex = vertices[i];
		fprintf(file_ptr,"v %f %f %f\n",vertex(0),vertex(1),vertex(2));
	}
	std::vector<Vector3f> normals = object->getNormals();
	bool has_normals = normals.size();
	for(int i=0;i<normals.size();i++)	{
		Vector3f normal = normals[i];
		fprintf(file_ptr,"vn %f %f %f\n",normal(0),normal(1),normal(2));
	}
	std::vector<Vector2f> tex_coords = object->getTextureCoords();
	bool has_tex_coords = tex_coords.size();
	for(int i=0;i<tex_coords.size();i++)	{
		Vector2f tex_coord = tex_coords[i];
		fprintf(file_ptr,"vt %f %f\n",tex_coord(0),tex_coord(1));
	}

	std::vector<Face *> faces = object->getFaces();
	for (int i=0;i<faces.size();i++)	{
		std::vector<int> vertex_indices = faces[i]->getVertices();
		fprintf(file_ptr,"f ");
		for (int v=0;v<vertex_indices.size();v++)	{
			fprintf(file_ptr,"%d",vertex_indices[v]+1);
			if (has_normals) {
				fprintf(file_ptr,"/%d",vertex_indices[v]+1);
			}
			if (has_tex_coords)	{
				fprintf(file_ptr,"/%d",vertex_indices[v]+1);
			}

			if (v+1 == vertex_indices.size())  {
				fprintf(file_ptr,"\n");
			}
			else	{
				fprintf(file_ptr," ");
			}
		}
	}
	fclose(file_ptr);

	return;
}

#endif
