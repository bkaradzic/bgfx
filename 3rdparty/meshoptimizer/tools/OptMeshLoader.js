THREE.OptMeshLoader = (function ()
{
	function OptMeshLoader(manager)
	{
		this.manager = (manager !== undefined) ? manager : THREE.DefaultLoadingManager;
		this.materials = Promise.resolve(null);
	}

	OptMeshLoader.prototype =
	{
		constructor: OptMeshLoader,

		load: function (url, onLoad, onProgress, onError)
		{
			var scope = this;

			var loader = new THREE.FileLoader(scope.manager);
			loader.setResponseType('arraybuffer');
			loader.setPath(this.path);
			loader.load(url, function (data)
			{
				scope.decoder.ready.then(function ()
				{
					scope.materials.then(function (materials)
					{
						onLoad(scope.parse(data, materials));
					});
				});
			}, onProgress, onError);
		},

		setDecoder: function (value)
		{
			this.decoder = value;
			return this;

		},

		setPath: function (value)
		{
			this.path = value;
			return this;
		},

		setMaterials: function (materials)
		{
			this.materials = Promise.resolve(materials);
			return this;
		},

		setMaterialLib: function (lib)
		{
			var scope = this;

			this.materials = new Promise(function (resolve, reject)
			{
				var loader = new THREE.MTLLoader();
				loader.setPath(scope.path);
				loader.load(lib, function (materials) { materials.preload(); resolve(materials); }, null, reject);
			});

			return this;
		},

		parse: function (data, materials)
		{
			console.time('OptMeshLoader');

			var array = new Uint8Array(data);
			var view = new DataView(data);

			var endian = true;
			var magic = view.getUint32(0, endian);
			var objectCount = view.getUint32(4, endian);
			var vertexCount = view.getUint32(8, endian);
			var indexCount = view.getUint32(12, endian);
			var vertexDataSize = view.getUint32(16, endian);
			var indexDataSize = view.getUint32(20, endian);
			var posOffsetX = view.getFloat32(24, endian);
			var posOffsetY = view.getFloat32(28, endian);
			var posOffsetZ = view.getFloat32(32, endian);
			var posScale = view.getFloat32(36, endian);
			var uvOffsetX = view.getFloat32(40, endian);
			var uvOffsetY = view.getFloat32(44, endian);
			var uvScaleX = view.getFloat32(48, endian);
			var uvScaleY = view.getFloat32(52, endian);

			if (magic != 0x4D54504F)
				throw new Error("Malformed mesh file: unrecognized header");

			var objectOffset = 64;
			var objectDataOffset = objectOffset + 16 * objectCount;

			var objectDataSize = 0;

			for (var i = 0; i < objectCount; ++i)
				objectDataSize += view.getUint32(objectOffset + 16 * i + 8, endian);

			var vertexDataOffset = objectDataOffset + objectDataSize;
			var indexDataOffset = vertexDataOffset + vertexDataSize;

			var endOffset = indexDataOffset + indexDataSize;

			if (endOffset != data.byteLength)
				throw new Error("Malformed mesh file: unexpected input size");

			var vertexSize = 16;
			var indexSize = 4;

			var vertexBuffer = new ArrayBuffer(vertexCount * vertexSize);
			var vertexBufferU8 = new Uint8Array(vertexBuffer);
			this.decoder.decodeVertexBuffer(vertexBufferU8, vertexCount, vertexSize, array.subarray(vertexDataOffset, vertexDataOffset + vertexDataSize));

			var indexBuffer = new ArrayBuffer(indexCount * indexSize);
			var indexBufferU8 = new Uint8Array(indexBuffer);
			this.decoder.decodeIndexBuffer(indexBufferU8, indexCount, indexSize, array.subarray(indexDataOffset, indexDataOffset + indexDataSize));

			var geometry = new THREE.BufferGeometry();

			geometry.addAttribute('position', new THREE.InterleavedBufferAttribute(new THREE.InterleavedBuffer(new Uint16Array(vertexBuffer), 8), 3, 0, false));
			geometry.addAttribute('normal', new THREE.InterleavedBufferAttribute(new THREE.InterleavedBuffer(new Int8Array(vertexBuffer), 16), 3, 8, true));
			geometry.addAttribute('uv', new THREE.InterleavedBufferAttribute(new THREE.InterleavedBuffer(new Uint16Array(vertexBuffer), 8), 2, 6, false));
			geometry.setIndex(new THREE.BufferAttribute(new Uint32Array(indexBuffer), 1, false));

			var objectDataOffsetAcc = objectDataOffset;

			var objectMaterials = [];
			var objectMaterialsLookup = {};

			for (var i = 0; i < objectCount; i++)
			{
				var objectIndexOffset = view.getUint32(objectOffset + 16 * i + 0, endian);
				var objectIndexCount = view.getUint32(objectOffset + 16 * i + 4, endian);
				var objectMaterialLength = view.getUint32(objectOffset + 16 * i + 8, endian);

				var objectMaterialName = String.fromCharCode.apply(null, array.subarray(objectDataOffsetAcc, objectDataOffsetAcc + objectMaterialLength));
				var objectMaterialIndex = objectMaterialsLookup[objectMaterialName];

				if (objectMaterialIndex == undefined)
				{
					var objectMaterial = null;

					if (materials !== null)
						objectMaterial = materials.create(objectMaterialName);

					if (!objectMaterial)
						objectMaterial = new THREE.MeshPhongMaterial();

					if (objectMaterial.map)
					{
						objectMaterial.map.offset.set(uvOffsetX, uvOffsetY);
						objectMaterial.map.repeat.set(uvScaleX, uvScaleY);
					}

					objectMaterialIndex = objectMaterials.length;
					objectMaterialsLookup[objectMaterialName] = objectMaterialIndex;
					objectMaterials.push(objectMaterial);
				}

				geometry.addGroup(objectIndexOffset, objectIndexCount, objectMaterialIndex);

				objectDataOffsetAcc += objectMaterialLength;
			}

			var mesh = new THREE.Mesh(geometry, objectMaterials);
			mesh.position.set(posOffsetX, posOffsetY, posOffsetZ);
			mesh.scale.set(posScale, posScale, posScale);

			var container = new THREE.Group();
			container.add(mesh);

			console.timeEnd('OptMeshLoader');

			return container;
		}
	};

	return OptMeshLoader;
})();
