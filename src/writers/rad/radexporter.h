/*****************************************************************************
	Glare

    Copyright (C) 2017  German Molina (germolinal@gmail.com)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*****************************************************************************/


#pragma once

//! The main object for exporting a GroundhogModel in Radiance format.
/*!
The file distribution will be the one used by Groundhog (www.groundhoglighting.com).

The main function to be called is RadExporter::exportModel()
*/
class RadExporter {
private:	
	GroundhogModel * model; //!< The GroundhogModel to export
	std::string exportDir; //!< The directory to exporit to
	bool verbose; //!< Should we inform progress?

public:

	//! Creates a RadExporter object
	/*!
	Each input is assigned to the corresponding member

	@author German Molina
	*/
	RadExporter(GroundhogModel * model, std::string exportDir, bool verbose);
	
	//! Destroys a RadExporter object
	/*!
	@author German Molina
	*/
	~RadExporter();

	//! Exports a GroundhogModel in Radiance format.
	/*!
	Will call other functions of the object with the purpose of creating
	directories and writing different files

	@author German Molina
	@return success
	*/
	bool exportModel();
	
	//! Writes the information of the model (north correction and location)
	/*!
	The information is written in the file 'model_info.txt'

	@author German Molina
	@return success
	@param[in] filename The subdirectory to export
	*/
	bool writeModelInfo(char * filename);
	
	//! Writes all the View objects in Radiance format in different files
	/*!
	A directory is created; and each View is stored in a '$viewName.vf' file

	@author German Molina
	@return success
	@param[in] dir The subdirectory to export
	*/
	bool writeViews(char * dir);

	//! Writes all the component definitions in different files
	/*!
	A directory is created; and a '$componentName.rad' file
	is created for each ComponentDefinition

	The files will be autocontained; that is, they have all the materials
	and geometry that defines the ComponentDefinition

	@author German Molina
	@return success
	@param[in] dir The subdirectory to export
	*/
	bool writeComponentDefinitions(char * dir);
	
	//! Writes all the layers in different files
	/*!
	A directory is created; and a 'layerName.rad' file
	is created for each Layer.

	The files will contain the references to ComponentDefinitions (using xform)
	and the geometry. Materials will be stored somewhere else in the directory

	@author German Molina
	@return success
	@param[in] dir The subdirectory to export
	*/
	bool writeLayers(char * dir);

	//! Writes a ComponentInstance in Radiance format
	/*!
	@author German Molina
	@param[in] file The file to write this in
	@param[in] instance The ComponentInstance to write
	*/
	void writeComponentInstance(std::ofstream * file, ComponentInstance * instance);
	
	//! Writes a Loop in Radiance format
	/*!
	@author German Molina
	@param[in] file The file to write this in
	@param[in] loop The Loop to write
	*/
	void writeLoop(std::ofstream * file, Loop * loop);
	
	//! Writes a Face in Radiance format
	/*!
	This is used when the Face does not Face::hasTooManyLoops

	@author German Molina
	@param[in] file The file to write this in
	@param[in] face The Face to write
	*/
	void writeClosedFace(std::ofstream * file, Face * face);

	//! Writes a Face in Radiance format
	/*!
	@author German Molina
	@param[in] file The file to write this in
	@param[in] face The Face to write
	@todo Support faces with many holes
	*/
	void writeFace(std::ofstream * file, Face * face);

	//! Writes all the window groups in Radiance format
	/*!
	@author German Molina
	@return success
	@param[in] dir The subdirectory to export
	*/
	bool writeWindows(char * dir);

	//! Writes all the Workplanes in Radiance format
	/*!
	@author German Molina
	@return success
	@param[in] dir The subdirectory to export
	*/
	bool writeWorkplanes(char * dir);

	//! Writes a Polygon3D that represents a Workplane
	/*!
	This method takes a Polygon3D with holes, triangulates it and writes
	the files required.

	@author German Molina
	@param[in] ptsFile The file where the points (sensors) get written
	@param[in] pxlFile The file where the pixels (i.e. triangles) get written
	@param[in] wp The Polygon3D to triangulate and write
	@return success
	*/
	bool writeWorkplane(std::ofstream * ptsFile, std::ofstream * pxlFile, Polygon3D * wp);

	//! Writes all the Material objects in Radiance format
	/*!
	@author German Molina
	@return success
	@param[in] dir The subdirectory to export
	*/
	bool writeMaterials(char * dir);

	//! Writes the standard Clear Sky
	/*!
	@author German Molina
	@return [Boolean] Success
	*/
	bool writeSky(char * dir);

	//! Writes the scene file
	/*!
	@author German Molina
	@return [Boolean] Success
	@todo There is a bug that would cause an error if the exporting Directory of Layers changes.
	*/
	bool writeSceneFile(char * dir);

	//! Writes the Photosensors
	/*!
	@author German Molina
	@return [Boolean] Success
	*/
	bool writePhotosensors(char * dir);

	
};
