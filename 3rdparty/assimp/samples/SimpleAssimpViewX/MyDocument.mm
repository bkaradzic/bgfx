//
//  MyDocument.m
//  DisplayLinkAsyncMoviePlayer
//
//  Created by vade on 10/26/10.
//  Copyright __MyCompanyName__ 2010 . All rights reserved.
//

#import "cimport.h"
#import "config.h"
#import "MyDocument.h"
#import <OpenGL/CGLMacro.h>

#pragma mark -
#pragma mark Helper Functions

#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)

static void color4_to_float4(const aiColor4D *c, float f[4])
{
	f[0] = c->r;
	f[1] = c->g;
	f[2] = c->b;
	f[3] = c->a;
}

static void set_float4(float f[4], float a, float b, float c, float d)
{
	f[0] = a;
	f[1] = b;
	f[2] = c;
	f[3] = d;
}

#pragma mark -
#pragma mark CVDisplayLink Callback
static CVReturn MyDisplayLinkCallback(CVDisplayLinkRef displayLink,const CVTimeStamp *inNow,const CVTimeStamp *inOutputTime,CVOptionFlags flagsIn,CVOptionFlags *flagsOut,void *displayLinkContext)
{
	CVReturn error = [(MyDocument*) displayLinkContext displayLinkRenderCallback:inOutputTime];
	return error;
}

#pragma mark -

@implementation MyDocument
@synthesize _view;

- (id)init 
{
    self = [super init];
    if (self != nil)
    {
        // initialization code
    }
    return self;
}

- (NSString *)windowNibName 
{
    return @"MyDocument";
}

- (void)windowControllerDidLoadNib:(NSWindowController *)windowController 
{
    [super windowControllerDidLoadNib:windowController];
    
    NSOpenGLPixelFormatAttribute attributes[] = 
	{
		NSOpenGLPFADoubleBuffer,
		NSOpenGLPFAAccelerated,
        NSOpenGLPFADepthSize, 24,
        NSOpenGLPFAMultisample,
        NSOpenGLPFASampleBuffers, 2,
		(NSOpenGLPixelFormatAttribute) 0
    };
    
    _glPixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attributes];

    if(!_glPixelFormat)
        NSLog(@"Error creating PF");
    
    _glContext = [[NSOpenGLContext alloc] initWithFormat:_glPixelFormat shareContext:nil];
    
    const GLint one = 1;
    
    [_glContext setValues:&one forParameter:NSOpenGLCPSwapInterval];
    [_glContext setView:_view];

    // Set up initial GL state.
    CGLContextObj cgl_ctx = (CGLContextObj)[_glContext CGLContextObj];
    
    glEnable(GL_MULTISAMPLE);
    
    glClearColor(0.3, 0.3, 0.3, 0.3);

    // enable color tracking
    //glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_TRUE);
    
    glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);

    glShadeModel(GL_SMOOTH);
    
    glEnable(GL_LIGHTING);
    
    GLfloat global_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    
    GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

    GLfloat diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

    GLfloat ambient[] = {0.2, 0.2f, 0.2f, 0.2f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

    GLfloat position[] = { 1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glEnable(GL_LIGHT0);
   
    // This is the only client state that always has to be set.
    glEnableClientState(GL_VERTEX_ARRAY); 

    // end GL State setup.
    
    // Display Link setup.
    CVReturn error = kCVReturnSuccess;
    
    error = CVDisplayLinkCreateWithActiveCGDisplays(&_displayLink);
    if(error == kCVReturnError)
        NSLog(@"Error Creating DisplayLink");
    
    error = CVDisplayLinkSetOutputCallback(_displayLink,MyDisplayLinkCallback, self);
    if(error == kCVReturnError)
        NSLog(@"Error Setting DisplayLink Callback");
    
    error = CVDisplayLinkStart(_displayLink);
    if(error == kCVReturnError)
        NSLog(@"Error Starting DisplayLink");

    NSOpenPanel* openPanel = [NSOpenPanel openPanel];
    
    [openPanel beginSheetModalForWindow:[_view window] completionHandler:^(NSInteger result) 
    {
        if (result == NSOKButton)
        {
            [openPanel orderOut:self]; // close panel before we might present an error
        
            if([[NSFileManager defaultManager] fileExistsAtPath:[openPanel filename]])
            {
                // Load our new path.
                
                // only ever give us triangles.
                aiPropertyStore* props = aiCreatePropertyStore();
                aiSetImportPropertyInteger(props, AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_LINE | aiPrimitiveType_POINT );
                
                NSUInteger aiPostProccesFlags;
                
                switch (2)
                {
                    case 0:
                        aiPostProccesFlags = aiProcessPreset_TargetRealtime_Fast;
                        break;                    
                    case 1:
                        aiPostProccesFlags = aiProcessPreset_TargetRealtime_Quality;
                        break;
                    case 2:
                        aiPostProccesFlags = aiProcessPreset_TargetRealtime_MaxQuality;
                        break;
                    default:
                        aiPostProccesFlags = aiProcessPreset_TargetRealtime_MaxQuality;
                        break;
                }
                
                // aiProcess_FlipUVs is needed for VAO / VBOs,  not sure why.
                _scene = (aiScene*) aiImportFileExWithProperties([[openPanel filename] cStringUsingEncoding:[NSString defaultCStringEncoding]], aiPostProccesFlags | aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_PreTransformVertices | 0, NULL, props);

                aiReleasePropertyStore(props);
                
                if (_scene)
                {       
                    textureDictionary = [[NSMutableDictionary alloc] initWithCapacity:5];
                    
                    // Why do I need to cast this !?
                    CGLContextObj cgl_ctx = (CGLContextObj)[_glContext CGLContextObj];
                    CGLLockContext(cgl_ctx);
                    
                    [self loadTexturesInContext:cgl_ctx withModelPath:[[openPanel filename] stringByStandardizingPath]];
                    
                    //NSDictionary* userInfo = [NSDictionary dictionaryWithObjectsAndKeys:[NSValue valueWithPointer:cgl_ctx], @"context", [self.inputModelPath stringByStandardizingPath], @"path", nil ];
                    //[self performSelectorInBackground:@selector(loadTexturesInBackground:) withObject:userInfo];
                    
                    [self getBoundingBoxWithMinVector:&scene_min maxVectr:&scene_max];
                    scene_center.x = (scene_min.x + scene_max.x) / 2.0f;
                    scene_center.y = (scene_min.y + scene_max.y) / 2.0f;
                    scene_center.z = (scene_min.z + scene_max.z) / 2.0f;
                    
                    // optional normalized scaling
                    normalizedScale = scene_max.x-scene_min.x;
                    normalizedScale = aisgl_max(scene_max.y - scene_min.y,normalizedScale);
                    normalizedScale = aisgl_max(scene_max.z - scene_min.z,normalizedScale);
                    normalizedScale = 1.f / normalizedScale;
                    
                    if(_scene->HasAnimations())
                        NSLog(@"scene has animations");
                                        
                    [self createGLResourcesInContext:cgl_ctx];
                    CGLUnlockContext(cgl_ctx);
                }
            }
        }            
    }]; // end block handler
}

- (void) close
{
    CVDisplayLinkStop(_displayLink);
    CVDisplayLinkRelease(_displayLink);
    
    if(_scene)
    {
        aiReleaseImport(_scene);
        _scene = NULL;
        
        CGLContextObj cgl_ctx = (CGLContextObj)[_glContext CGLContextObj];
        glDeleteTextures([textureDictionary count], textureIds);
        
        [textureDictionary release];
        textureDictionary = nil;
        
        free(textureIds);
        textureIds = NULL;
        
        [self deleteGLResourcesInContext:cgl_ctx];
    }    
    
    [_glContext release];
    _glContext = nil;
    
    [_glPixelFormat release];
    _glPixelFormat = nil;
    
    [super close];
}

- (CVReturn)displayLinkRenderCallback:(const CVTimeStamp *)timeStamp
{
    CVReturn rv = kCVReturnError;
    NSAutoreleasePool *pool;
	
    pool = [[NSAutoreleasePool alloc] init];
    {
        [self render];
		rv = kCVReturnSuccess;
    }
    [pool release];
    return rv;
}

- (void) render
{   
    CGLContextObj cgl_ctx = (CGLContextObj)[_glContext CGLContextObj];
    CGLLockContext(cgl_ctx);
        
    [_glContext update];
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glViewport(0, 0, _view.frame.size.width, _view.frame.size.height);

    GLfloat aspect = _view.frame.size.height/_view.frame.size.width; 
    glOrtho(-1, 1, - (aspect), aspect, -10, 10);
        
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glTranslated(0.0, 0.0, 1.0);
    
    // Draw our GL model.    
    if(_scene)
    {
        glScaled(normalizedScale , normalizedScale, normalizedScale);
        // center the model
        glTranslated( -scene_center.x, -scene_center.y, -scene_center.z);    
        
        glScaled(2.0, 2.0, 2.0);
        
        static float i = 0;
        i+=0.5;
        glRotated(i, 0, 1, 0);
        
        [self drawMeshesInContext:cgl_ctx];
    }

    CGLUnlockContext(cgl_ctx);
    
    CGLFlushDrawable(cgl_ctx);
}

#pragma mark -
#pragma mark Loading 

// Inspired by LoadAsset() & CreateAssetData() from AssimpView D3D project
- (void) createGLResourcesInContext:(CGLContextObj)cgl_ctx
{
    // create new mesh helpers for each mesh, will populate their data later.
    modelMeshes = [[NSMutableArray alloc] initWithCapacity:_scene->mNumMeshes];
    
    // create OpenGL buffers and populate them based on each meshes pertinant info.
    for (unsigned int i = 0; i < _scene->mNumMeshes; ++i)
    {
        NSLog(@"%u", i);
        
        // current mesh we are introspecting
        const aiMesh* mesh = _scene->mMeshes[i];
        
        // the current meshHelper we will be populating data into.
        MeshHelper* meshHelper = [[MeshHelper alloc] init];

        // Handle material info
        
        aiMaterial* mtl = _scene->mMaterials[mesh->mMaterialIndex];
        
        // Textures
        int texIndex = 0;
        aiString texPath;
        
        if(AI_SUCCESS == mtl->GetTexture(aiTextureType_DIFFUSE, texIndex, &texPath))
        {
            NSString* textureKey = [NSString stringWithCString:texPath.data encoding:[NSString defaultCStringEncoding]];
            //bind texture
            NSNumber* textureNumber = (NSNumber*)[textureDictionary valueForKey:textureKey];
            
            //NSLog(@"applyMaterialInContext: have texture %i", [textureNumber unsignedIntValue]); 
            meshHelper.textureID = [textureNumber unsignedIntValue];		
        }
        else
            meshHelper.textureID = 0;
        
        // Colors
        
        aiColor4D dcolor = aiColor4D(0.8f, 0.8f, 0.8f, 1.0f);
        if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &dcolor))
            [meshHelper setDiffuseColor:&dcolor];
        
        aiColor4D scolor = aiColor4D(0.0f, 0.0f, 0.0f, 1.0f);
        if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &scolor))
            [meshHelper setSpecularColor:&scolor];
        
        aiColor4D acolor = aiColor4D(0.2f, 0.2f, 0.2f, 1.0f);
        if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &acolor))
            [meshHelper setAmbientColor:&acolor];
        
        aiColor4D ecolor = aiColor4D(0.0f, 0.0f, 0.0f, 1.0f);
        if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &ecolor))
            [meshHelper setEmissiveColor:&ecolor];
        
        // Culling
        unsigned int max = 1;
        int two_sided;
        if((AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_TWOSIDED, &two_sided, &max)) && two_sided)
            [meshHelper setTwoSided:YES];
        else
            [meshHelper setTwoSided:NO];
        
        // Create a VBO for our vertices
        
        GLuint vhandle;
        glGenBuffers(1, &vhandle);
        
        glBindBuffer(GL_ARRAY_BUFFER, vhandle);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh->mNumVertices, NULL, GL_STATIC_DRAW);
        
        // populate vertices
        Vertex* verts = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER_ARB, GL_WRITE_ONLY_ARB);
        
        for (unsigned int x = 0; x < mesh->mNumVertices; ++x)
        {
            verts->vPosition = mesh->mVertices[x];
            
            if (NULL == mesh->mNormals)
                verts->vNormal = aiVector3D(0.0f,0.0f,0.0f);
            else
                verts->vNormal = mesh->mNormals[x];
            
            if (NULL == mesh->mTangents)
            {
                verts->vTangent = aiVector3D(0.0f,0.0f,0.0f);
                verts->vBitangent = aiVector3D(0.0f,0.0f,0.0f);
            }
            else
            {
                verts->vTangent = mesh->mTangents[x];
                verts->vBitangent = mesh->mBitangents[x];
            }
            
            if (mesh->HasVertexColors(0))
            {
                verts->dColorDiffuse = mesh->mColors[0][x];
            }
            else
                verts->dColorDiffuse = aiColor4D(1.0, 1.0, 1.0, 1.0);
            
            // This varies slightly form Assimp View, we support the 3rd texture component.
            if (mesh->HasTextureCoords(0))
                verts->vTextureUV = mesh->mTextureCoords[0][x];
            else
                verts->vTextureUV = aiVector3D(0.5f,0.5f, 0.0f);
            
            if (mesh->HasTextureCoords(1))
                verts->vTextureUV2 = mesh->mTextureCoords[1][x];
            else 
                verts->vTextureUV2 = aiVector3D(0.5f,0.5f, 0.0f);
            
            // TODO: handle Bone indices and weights
            /*          if( mesh->HasBones())
             {
             unsigned char boneIndices[4] = { 0, 0, 0, 0 };
             unsigned char boneWeights[4] = { 0, 0, 0, 0 };
             ai_assert( weightsPerVertex[x].size() <= 4);
             
             for( unsigned int a = 0; a < weightsPerVertex[x].size(); a++)
             {
             boneIndices[a] = weightsPerVertex[x][a].mVertexId;
             boneWeights[a] = (unsigned char) (weightsPerVertex[x][a].mWeight * 255.0f);
             }
             
             memcpy( verts->mBoneIndices, boneIndices, sizeof( boneIndices));
             memcpy( verts->mBoneWeights, boneWeights, sizeof( boneWeights));
             }
             else
             */ 
            {
                memset( verts->mBoneIndices, 0, sizeof( verts->mBoneIndices));
                memset( verts->mBoneWeights, 0, sizeof( verts->mBoneWeights));
            }
            
            ++verts;
        }
        
        glUnmapBufferARB(GL_ARRAY_BUFFER_ARB); //invalidates verts
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        // set the mesh vertex buffer handle to our new vertex buffer.
        meshHelper.vertexBuffer = vhandle;
        
        // Create Index Buffer
        
        // populate the index buffer.
        NSUInteger nidx;
        switch (mesh->mPrimitiveTypes)
        {
            case aiPrimitiveType_POINT:
                nidx = 1;break;
            case aiPrimitiveType_LINE:
                nidx = 2;break;
            case aiPrimitiveType_TRIANGLE:
                nidx = 3;break;
            default: assert(false);
        }   
        
        // create the index buffer
        GLuint ihandle;
        glGenBuffers(1, &ihandle);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ihandle);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh->mNumFaces * nidx, NULL, GL_STATIC_DRAW);
        
        unsigned int* indices = (unsigned int*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY_ARB);
        
        // now fill the index buffer
        for (unsigned int x = 0; x < mesh->mNumFaces; ++x)
        {
            for (unsigned int a = 0; a < nidx; ++a)
            {
                //                 if(mesh->mFaces[x].mNumIndices != 3)
                //                     NSLog(@"whoa don't have 3 indices...");
                
                *indices++ = mesh->mFaces[x].mIndices[a];
            }
        }
        
        glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        
        // set the mesh index buffer handle to our new index buffer.
        meshHelper.indexBuffer = ihandle;
        meshHelper.numIndices = mesh->mNumFaces * nidx;
        
        // create the normal buffer. Assimp View creates a second normal buffer. Unsure why. Using only the interleaved normals for now.
        // This is here for reference.
        
        /*          GLuint nhandle;
         glGenBuffers(1, &nhandle);
         glBindBuffer(GL_ARRAY_BUFFER, nhandle);
         glBufferData(GL_ARRAY_BUFFER, sizeof(aiVector3D)* mesh->mNumVertices, NULL, GL_STATIC_DRAW);
         
         // populate normals
         aiVector3D* normals = (aiVector3D*)glMapBuffer(GL_ARRAY_BUFFER_ARB, GL_WRITE_ONLY_ARB);
         
         for (unsigned int x = 0; x < mesh->mNumVertices; ++x)
         {
         aiVector3D vNormal = mesh->mNormals[x];
         *normals = vNormal;
         ++normals;
         }
         
         glUnmapBufferARB(GL_ARRAY_BUFFER_ARB); //invalidates verts
         glBindBuffer(GL_ARRAY_BUFFER, 0);
         
         meshHelper.normalBuffer = nhandle;
         */
        
        // Create VAO and populate it
        
        GLuint vaoHandle; 
        glGenVertexArraysAPPLE(1, &vaoHandle);
        
        glBindVertexArrayAPPLE(vaoHandle);
        
        
        glBindBuffer(GL_ARRAY_BUFFER, meshHelper.vertexBuffer);
        
        glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(12));
        
        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(4, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(24));
        
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(64));
        //TODO: handle second texture
        
        // VertexPointer ought to come last, apparently this is some optimization, since if its set once, first, it gets fiddled with every time something else is update.
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, sizeof(Vertex), 0);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshHelper.indexBuffer);
        
        glBindVertexArrayAPPLE(0);
        
        // save the VAO handle into our mesh helper
        meshHelper.vao = vaoHandle;
        
        // Create the display list
        
        GLuint list = glGenLists(1);
        
        glNewList(list, GL_COMPILE);
        
        float dc[4];
        float sc[4];
        float ac[4];
        float emc[4];        
        
        // Material colors and properties
        color4_to_float4([meshHelper diffuseColor], dc);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dc);
        
        color4_to_float4([meshHelper specularColor], sc);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, sc);
        
        color4_to_float4([meshHelper ambientColor], ac);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ac);
        
        color4_to_float4(meshHelper.emissiveColor, emc);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emc);
        
        glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

        // Culling
        if(meshHelper.twoSided)
            glEnable(GL_CULL_FACE);
        else 
            glDisable(GL_CULL_FACE);
        
        
        // Texture Binding
        glBindTexture(GL_TEXTURE_2D, meshHelper.textureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
        
        // This binds the whole VAO, inheriting all the buffer and client state. Weeee
        glBindVertexArrayAPPLE(meshHelper.vao);        
        glDrawElements(GL_TRIANGLES, meshHelper.numIndices, GL_UNSIGNED_INT, 0);
        
        glEndList();
        
        meshHelper.displayList = list;
        
        // Whew, done. Save all of this shit.
        [modelMeshes addObject:meshHelper];
        
        [meshHelper release];
    }
}

- (void) deleteGLResourcesInContext:(CGLContextObj)cgl_ctx
{    
    for(MeshHelper* helper in modelMeshes)
    {
        const GLuint indexBuffer = helper.indexBuffer;
        const GLuint vertexBuffer = helper.vertexBuffer;
        const GLuint normalBuffer = helper.normalBuffer;
        const GLuint vaoHandle = helper.vao;
        const GLuint dlist = helper.displayList;
        
        glDeleteBuffers(1, &vertexBuffer);
        glDeleteBuffers(1, &indexBuffer);
        glDeleteBuffers(1, &normalBuffer);
        glDeleteVertexArraysAPPLE(1, &vaoHandle);
        
        glDeleteLists(1, dlist);
        
        helper.indexBuffer = 0;
        helper.vertexBuffer = 0;
        helper.normalBuffer = 0;
        helper.vao = 0;
        helper.displayList = 0;
    }
    
    [modelMeshes release];
    modelMeshes = nil;
}

- (void) drawMeshesInContext:(CGLContextObj)cgl_ctx
{
    for(MeshHelper* helper in modelMeshes)
    {
        // Set up meterial state.
        glCallList(helper.displayList);  
    }
}


- (void) loadTexturesInContext:(CGLContextObj)cgl_ctx withModelPath:(NSString*) modelPath
{    
    if (_scene->HasTextures())
    {
        NSLog(@"Support for meshes with embedded textures is not implemented");
        return;
    }
    
    /* getTexture Filenames and Numb of Textures */
	for (unsigned int m = 0; m < _scene->mNumMaterials; m++)
	{		
		int texIndex = 0;
		aiReturn texFound = AI_SUCCESS;
        
		aiString path;	// filename
        
        // TODO: handle other aiTextureTypes
		while (texFound == AI_SUCCESS)
		{
			texFound = _scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
            
            NSString* texturePath = [NSString stringWithCString:path.data encoding:[NSString defaultCStringEncoding]];
            
            // add our path to the texture and the index to our texture dictionary.
            [textureDictionary setValue:[NSNumber numberWithUnsignedInt:texIndex] forKey:texturePath];
            
			texIndex++;
		}		
	}
    
    textureIds = (GLuint*) malloc(sizeof(GLuint) * [textureDictionary count]); //new GLuint[ [textureDictionary count] ];
    glGenTextures([textureDictionary count], textureIds);
    
    NSLog(@"textureDictionary: %@", textureDictionary);
    
    // create our textures, populate them, and alter our textureID value for the specific textureID we create.
    
    // so we can modify while we enumerate... 
    NSDictionary *textureCopy = [textureDictionary copy];
    
    // GCD attempt.
    //dispatch_sync(_queue, ^{
    
    int i = 0;
    
    for(NSString* texturePath in textureCopy)
    {        
        NSString* fullTexturePath = [[[modelPath stringByDeletingLastPathComponent] stringByAppendingPathComponent:[texturePath stringByStandardizingPath]] stringByStandardizingPath];
        NSLog(@"texturePath: %@", fullTexturePath);
        
        NSImage* textureImage = [[NSImage alloc] initWithContentsOfFile:fullTexturePath];
        
        if(textureImage)
        {
            //NSLog(@"Have Texture Image");
            NSBitmapImageRep* bitmap = [NSBitmapImageRep alloc];
            
            [textureImage lockFocus];
            [bitmap initWithFocusedViewRect:NSMakeRect(0, 0, textureImage.size.width, textureImage.size.height)];
            [textureImage unlockFocus];
            
            glActiveTexture(GL_TEXTURE0);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, textureIds[i]);
            //glPixelStorei(GL_UNPACK_ROW_LENGTH, [bitmap pixelsWide]);
            //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            
            // generate mip maps
            glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR); 
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
            
            // draw into our bitmap
            int samplesPerPixel = [bitmap samplesPerPixel];
            
            if(![bitmap isPlanar] && (samplesPerPixel == 3 || samplesPerPixel == 4))
            {
                glTexImage2D(GL_TEXTURE_2D,
                             0,
                             //samplesPerPixel == 4 ? GL_COMPRESSED_RGBA_S3TC_DXT3_EXT : GL_COMPRESSED_RGB_S3TC_DXT1_EXT, 
                             samplesPerPixel == 4 ? GL_RGBA8 : GL_RGB8,
                             [bitmap pixelsWide],
                             [bitmap pixelsHigh],
                             0,
                             samplesPerPixel == 4 ? GL_RGBA : GL_RGB,
                             GL_UNSIGNED_BYTE,
                             [bitmap bitmapData]);
                
            } 
            
            
            // update our dictionary to contain the proper textureID value (from out array of generated IDs)
            [textureDictionary setValue:[NSNumber numberWithUnsignedInt:textureIds[i]] forKey:texturePath];
            
            [bitmap release];
        }
        else
        {
            [textureDictionary removeObjectForKey:texturePath];
            NSLog(@"Could not Load Texture: %@, removing reference to it.", fullTexturePath);
        }
        
        [textureImage release];
        i++;
    }       
    //});
    
    [textureCopy release];
    
}

- (void) getBoundingBoxWithMinVector:(aiVector3D*) min maxVectr:(aiVector3D*) max
{
	aiMatrix4x4 trafo;
	aiIdentityMatrix4(&trafo);
    
	min->x = min->y = min->z =  1e10f;
	max->x = max->y = max->z = -1e10f;
    
    [self getBoundingBoxForNode:_scene->mRootNode minVector:min maxVector:max matrix:&trafo];
}

- (void) getBoundingBoxForNode:(const aiNode*)nd  minVector:(aiVector3D*) min maxVector:(aiVector3D*) max matrix:(aiMatrix4x4*) trafo
{
	aiMatrix4x4 prev;
	unsigned int n = 0, t;
    
	prev = *trafo;
	aiMultiplyMatrix4(trafo,&nd->mTransformation);
    
	for (; n < nd->mNumMeshes; ++n)
    {
		const aiMesh* mesh = _scene->mMeshes[nd->mMeshes[n]];
		for (t = 0; t < mesh->mNumVertices; ++t)
        {
        	aiVector3D tmp = mesh->mVertices[t];
			aiTransformVecByMatrix4(&tmp,trafo);
            
			min->x = aisgl_min(min->x,tmp.x);
			min->y = aisgl_min(min->y,tmp.y);
			min->z = aisgl_min(min->z,tmp.z);
            
			max->x = aisgl_max(max->x,tmp.x);
			max->y = aisgl_max(max->y,tmp.y);
			max->z = aisgl_max(max->z,tmp.z);
		}
	}
    
	for (n = 0; n < nd->mNumChildren; ++n) 
    {
		[self getBoundingBoxForNode:nd->mChildren[n] minVector:min maxVector:max matrix:trafo];
	}
    
	*trafo = prev;
}


@end
