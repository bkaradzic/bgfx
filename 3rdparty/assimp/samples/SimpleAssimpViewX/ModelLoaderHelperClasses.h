//
//  v002MeshHelper.h
//  v002 Model Importer
//
//  Created by vade on 9/26/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <OpenGL/OpenGL.h>
#import "color4.h"
#import "vector3.h"
#import "vector2.h"
#import "matrix4x4.h"

/* workflow:

 1) create a new scene wrapper 
 2) populate an array of of meshHelpers for each mesh in the original scene
 3) (eventually) create an animator instance
 4) scale the asset (needed?)
 5) create the asset data (GL resources, textures etc)
    5a) for each mesh create a material instance
    5b) create a static vertex buffer
    5c) create index buffer
    5d) populate the index buffer
    5e) (eventually) gather weights    
*/

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

struct Vertex 
{
    aiVector3D vPosition;
    aiVector3D vNormal;
    
    aiColor4D  dColorDiffuse;
    aiVector3D vTangent;
    aiVector3D vBitangent;
    aiVector3D vTextureUV;
    aiVector3D vTextureUV2;
    unsigned char mBoneIndices[4];
    unsigned char mBoneWeights[4]; // last Weight not used, calculated inside the vertex shader
};


// Helper Class to store GPU related resources from a given aiMesh
// Modeled after AssimpView asset helper
@interface MeshHelper : NSObject 
{        
    // Display list ID, this one shots *all drawing* of the mesh. Only ever use this to draw. Booya.
    GLuint displayList;
    
    // VAO that encapsulates all VBO drawing state
    GLuint vao;
    
    // VBOs
    GLuint vertexBuffer;
    GLuint indexBuffer;
    GLuint normalBuffer;
    GLuint numIndices;
        
    // texture
    GLuint textureID;
    
    // Material 
    aiColor4D diffuseColor;
    aiColor4D specularColor;
    aiColor4D ambientColor;
    aiColor4D emissiveColor;
    
    GLfloat opacity;
    GLfloat shininess;
    GLfloat specularStrength;
    
    BOOL twoSided;
}

@property (readwrite, assign) GLuint vao;
@property (readwrite, assign) GLuint displayList;

@property (readwrite, assign) GLuint vertexBuffer;
@property (readwrite, assign) GLuint indexBuffer;
@property (readwrite, assign) GLuint normalBuffer;
@property (readwrite, assign) GLuint numIndices;

@property (readwrite, assign) GLuint textureID;

@property (readwrite, assign) aiColor4D* diffuseColor;
@property (readwrite, assign) aiColor4D* specularColor;
@property (readwrite, assign) aiColor4D* ambientColor;
@property (readwrite, assign) aiColor4D* emissiveColor;

@property (readwrite, assign) GLfloat opacity;
@property (readwrite, assign) GLfloat shininess;
@property (readwrite, assign) GLfloat specularStrength;
@property (readwrite, assign) BOOL twoSided;
@end
