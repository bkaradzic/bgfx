/* Babylon.js extension for MESHOPT_compression; requires Babylon.js 4.1 */
var NAME = "MESHOPT_compression";
var MESHOPT_compression = /** @class */ (function () {
    /** @hidden */
    function MESHOPT_compression(loader, decoder) {
        /** The name of this extension. */
        this.name = NAME;
        /** Defines whether this extension is enabled. */
        this.enabled = true;
        this._loader = loader;
        this._decoder = decoder;
    }
    /** @hidden */
    MESHOPT_compression.prototype.dispose = function () {
        delete this._loader;
    };
    /** @hidden */
    MESHOPT_compression.prototype.loadBufferViewAsync = function (context, bufferView) {
        if (bufferView.extensions && bufferView.extensions[NAME]) {
            var extensionDef = bufferView.extensions[NAME];
            if (extensionDef._decoded) {
                return extensionDef._decoded;
            }
            var view = this._loader.loadBufferViewAsync(context, extensionDef);
            var decoder = this._decoder;
            extensionDef._decoded = Promise.all([view, decoder.ready]).then(function (res) {
                var source = res[0];
                var count = extensionDef.count;
                var stride = extensionDef.byteStride;
                var result = new Uint8Array(new ArrayBuffer(count * stride));
                switch (extensionDef.mode) {
                    case 0:
                        decoder.decodeVertexBuffer(result, count, stride, source);
                        break;
                    case 1:
                        decoder.decodeIndexBuffer(result, count, stride, source);
                        break;
                    default:
                        throw new Error("GLTFLoader: Unrecognized meshopt compression mode.");
                }
                return Promise.resolve(result);
            });
            return extensionDef._decoded;
        } else {
            return null;
        }
    };
    return MESHOPT_compression;
}());
/* BABYLON.GLTF2.GLTFLoader.RegisterExtension("MESHOPT_compression", (loader) => new MESHOPT_compression(loader, MeshoptDecoder)); */
