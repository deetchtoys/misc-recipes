local ffi = require('ffi')
ffi.cdef[[
    typedef struct FaceManager FaceManager;

    FaceManager * FaceManagerNew();
    void FaceManagerDelete(FaceManager * faceManager);
    int FaceManagerRegisterFace(FaceManager * faceManager, int age, const char *buffer);
]]

local face_manager_lib = ffi.load('facemanagertest')
local face_manager = ffi.gc(face_manager_lib.FaceManagerNew(), face_manager_lib.FaceManagerDelete)
local s = "123"
face_manager_lib.FaceManagerRegisterFace(face_manager, 10, s)

return face_manager
