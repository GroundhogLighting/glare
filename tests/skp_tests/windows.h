#pragma once


#include "./common.h"


TEST(SKPRead, small_square_window)
{
    FOR_ALL_VERSIONS {
        ASSERT_LOAD_MODEL("small_square_window",version);
        
        // Only two layer
        size_t nLayers = model.getNumLayers();
        ASSERT_EQ(nLayers,2);
        
        // Check names
        ASSERT_EQ(model.getLayerRef(0)->getName(), "Layer0");
        ASSERT_EQ(model.getLayerRef(1)->getName(), "Layer1");
        
        // Count components in the component
        size_t nComponents = model.getNumComponentDefinitions();
        ASSERT_EQ(nComponents,0);
        
        // Check number of window groups
        ASSERT_EQ(1,model.getNumWindowGroups());
        
        // Check the Illum Group
        WindowGroup * wg = model.getWindowGroupRef(0);
        ASSERT_EQ(wg->size(),1);
        
        Loop * loop = wg->getWindowRef(0)->getOuterLoopRef();
        
        size_t nVertices = loop->size();
        ASSERT_EQ(nVertices,4);
        
        Point3D a = loop->getVertexRef(0);
        Point3D b = loop->getVertexRef(1);
        Point3D c = loop->getVertexRef(2);
        Point3D d = loop->getVertexRef(3);
        
        ASSERT_TRUE(a.isEqual(Point3D(0,0,0)) || a.isEqual(Point3D(0,1,0)) || a.isEqual(Point3D(1,0,0)) || a.isEqual(Point3D(1,1,0)));
        ASSERT_TRUE(b.isEqual(Point3D(0,0,0)) || b.isEqual(Point3D(0,1,0)) || b.isEqual(Point3D(1,0,0)) || b.isEqual(Point3D(1,1,0)));
        ASSERT_TRUE(c.isEqual(Point3D(0,0,0)) || c.isEqual(Point3D(0,1,0)) || c.isEqual(Point3D(1,0,0)) || c.isEqual(Point3D(1,1,0)));
        ASSERT_TRUE(d.isEqual(Point3D(0,0,0)) || d.isEqual(Point3D(0,1,0)) || d.isEqual(Point3D(1,0,0)) || d.isEqual(Point3D(1,1,0)));
        
        
        // Check number of materials... One material: the default glass
        ASSERT_EQ(model.getNumMaterials(),1);
    }
    
}


TEST(SKPRead, window_group)
{
    FOR_ALL_VERSIONS {
        ASSERT_LOAD_MODEL("window_group",version);
        
        // Check number of window groups
        ASSERT_EQ(1,model.getNumWindowGroups());
        
        // Check the window Group
        WindowGroup * wg = model.getWindowGroupRef(0);
        ASSERT_EQ(wg->size(),4);
        
        // Check name
        ASSERT_EQ(wg->getName(),"WINDOWS");
    }
}


