

/*****************************************************************************
 Emp
 
 Copyright (C) 2018  German Molina (germolinal@gmail.com)
 
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

#include "./CalculateDaylightFactor.h"
#include "taskmanager/static_simulation_task.h"

class CheckDFCompliance : public StaticSimulationTask {
    
public:
    
    
    CheckDFCompliance(std::string name, EmpModel * theModel, RTraceOptions * theOptions, Workplane * wp, double min, double max)
    {
        model = theModel;
        workplane = wp;
        minLux = min;
        maxLux = max;
        
        // Dependency
        CalculateDaylightFactor * dep = new CalculateDaylightFactor(theModel, theOptions, wp);
        addDependency(dep);
        
        depResults = &(dep->result); 
        
        // Set the name
        setName(&name);
    }
    
    CheckDFCompliance(std::string name, EmpModel * theModel, RTraceOptions * theOptions, std::vector<RAY> * theRays, double min, double max)
    {
        model = theModel;
        rays = theRays;
        minLux = min;
        maxLux = max;
        
        // Dependency
        CalculateDaylightFactor * dep = new CalculateDaylightFactor(theModel, theOptions, theRays);
        addDependency(dep);
        
        depResults = &(dep->result);
        
        // Set the name
        setName(&name);
    }
    
    Matrix * getDependencyResults()
    {
        return &(static_cast< CalculateDaylightFactor *>(getDependencyRef(0))->result);
    }
    
    
};

extern CheckDFCompliance checkDF;

