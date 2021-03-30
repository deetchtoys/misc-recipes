local ffi = require('ffi')
ffi.cdef[[
    typedef struct FaceManager FaceManager;

    FaceManager * FaceManagerNew();
    void FaceManagerDelete(FaceManager * faceManager);
    void FaceManagerReg(FaceManager *faceManager,
                        const char *imgData,
                        int imgDataLength,
                        char *jsonResponseBuffer,
                        int jsonResponseBufferSize);
    void FaceManagerIdentify(FaceManager *faceManager,
                             const char *jsonFeatures,
                             char *jsonResponseBuffer,
                             int jsonResponseBufferSize);
]]

local face_manager_lib = ffi.load('facemanagertest')
local face_manager = ffi.gc(face_manager_lib.FaceManagerNew(), face_manager_lib.FaceManagerDelete)

local file_handler = io.open("/home/seventh/images/wdq.png", "r")
local file_buffer = file_handler:read("*a")

ffi.new
face_manager_lib.FaceManagerReg(face_manager, file_buffer, string.len(file_buffer), )

local jsonFeatures = '{"age" : 10, "imgId" : "123", "data" : [1.1, 2.2, 3.3]}'
face_manager_lib.FaceManagerIdentify(face_manager, jsonFeatures)
