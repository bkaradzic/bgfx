//
//  v002MeshHelper.m
//  v002 Model Importer
//
//  Created by vade on 9/26/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "ModelLoaderHelperClasses.h"


@implementation MeshHelper

@synthesize vao;
@synthesize displayList;

@synthesize vertexBuffer;
@synthesize indexBuffer;
@synthesize normalBuffer;
@synthesize numIndices;

@synthesize textureID;

@dynamic diffuseColor;
@dynamic specularColor;
@dynamic ambientColor;
@dynamic emissiveColor;

@synthesize opacity;
@synthesize shininess;
@synthesize specularStrength;
@synthesize twoSided;

- (id) init
{
    if((self = [super init]))
    {
        diffuseColor = aiColor4D(0.8, 0.8, 0.8, 1.0);
        specularColor = aiColor4D(0.0f, 0.0f, 0.0f, 1.0f);
        ambientColor = aiColor4D(0.2f, 0.2f, 0.2f, 1.0f);
        emissiveColor = aiColor4D(0.0f, 0.0f, 0.0f, 1.0f);
    }
    return self; 
}

- (void) setDiffuseColor:(aiColor4D*) color;
{
    diffuseColor.r = color->r;
    diffuseColor.g = color->g;
    diffuseColor.b = color->b;
    diffuseColor.a = color->a;
}

- (aiColor4D*) diffuseColor
{
    return &diffuseColor;
}

- (void) setSpecularColor:(aiColor4D*) color;
{
    specularColor.r = color->r;
    specularColor.g = color->g;
    specularColor.b = color->b;
    specularColor.a = color->a;
}

- (aiColor4D*) specularColor
{
    return &specularColor;
}

- (void) setAmbientColor:(aiColor4D*) color;
{
    ambientColor.r = color->r;
    ambientColor.g = color->g;
    ambientColor.b = color->b;
    ambientColor.a = color->a;
}

- (aiColor4D*) ambientColor
{
    return &ambientColor;
}

- (void) setEmissiveColor:(aiColor4D*) color;
{
    emissiveColor.r = color->r;
    emissiveColor.g = color->g;
    emissiveColor.b = color->b;
    emissiveColor.a = color->a;
}

- (aiColor4D*) emissiveColor
{
    return &emissiveColor;
}


@end
