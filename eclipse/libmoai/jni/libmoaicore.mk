#================================================================#
# libmoaicore
#================================================================#
include $(CLEAR_VARS)

LOCAL_MODULE := libmoaicore
LOCAL_LDLIBS := -llog -lstring -lm -lz -lGLESv2.so -lGLESv1_CM.so

#----------------------------------------------------------------#
# header search paths
#----------------------------------------------------------------#
LOCAL_C_INCLUDES := $(SRC_PATH)/src \
$(SRC_PATH)/src/moaicore \
$(SRC_PATH)/src/uslsext \
$(SRC_PATH)/src/uslscore \
$(SRC_PATH)/src/contrib \
$(SRC_PATH)/src/zipfs \
$(SRC_PATH)/src/moai-lua-5.1.3/src \
$(SRC_PATH)/3rdparty \
$(SRC_PATH)/3rdparty/expat-2.0.1/amiga \
$(SRC_PATH)/3rdparty/expat-2.0.1/lib \
$(SRC_PATH)/3rdparty/expat-2.0.1/xmlwf \
$(SRC_PATH)/3rdparty/freetype-2.4.4/include \
$(SRC_PATH)/3rdparty/freetype-2.4.4/include/freetype \
$(SRC_PATH)/3rdparty/freetype-2.4.4/include/freetype2 \
$(SRC_PATH)/3rdparty/freetype-2.4.4/builds \
$(SRC_PATH)/3rdparty/freetype-2.4.4/src \
$(SRC_PATH)/3rdparty/freetype-2.4.4/config \
$(SRC_PATH)/3rdparty/jansson-2.1/src \
$(SRC_PATH)/3rdparty/jpeg-8c \
$(SRC_PATH)/3rdparty/lpng140 \
$(SRC_PATH)/3rdparty/curl-7.19.7/include-android\
$(SRC_PATH)/3rdparty/sqlite-3.6.16 \
$(SRC_PATH)/3rdparty/tinyxml \
$(SRC_PATH)/3rdparty/chipmunk-5.3.4/include \
$(SRC_PATH)/3rdparty/chipmunk-5.3.4/include/chipmunk \
$(SRC_PATH)/3rdparty/chipmunk-5.3.4/include/chipmunk/constraints \
$(SRC_PATH)/3rdparty/box2d-2.1.2/Box2D \
$(SRC_PATH)/3rdparty/box2d-2.1.2/Box2D/Box2D \
$(SRC_PATH)/3rdparty/box2d-2.1.2/Box2D/Box2D/Collision/Shapes \
$(SRC_PATH)/3rdparty/box2d-2.1.2/Box2D/Box2D/Collision \
$(SRC_PATH)/3rdparty/box2d-2.1.2/Box2D/Box2D/Common \
$(SRC_PATH)/3rdparty/box2d-2.1.2/Box2D/Box2D/Dynamics \
$(SRC_PATH)/3rdparty/box2d-2.1.2/Box2D/Box2D/Dynamics/Contacts \
$(SRC_PATH)/3rdparty/box2d-2.1.2/Box2D/Box2D/Dynamics/Joints \

#----------------------------------------------------------------#
# included files
#----------------------------------------------------------------#
LOCAL_SRC_FILES := $(SRC_PATH)/src/moaicore/moaicore-pch.cpp \
$(SRC_PATH)/src/moaicore/MOAIAction.cpp \
$(SRC_PATH)/src/moaicore/MOAIActionMgr.cpp \
$(SRC_PATH)/src/moaicore/MOAIAnim.cpp \
$(SRC_PATH)/src/moaicore/MOAIAnimCurve.cpp \
$(SRC_PATH)/src/moaicore/MOAIBitmapFontRipper.cpp \
$(SRC_PATH)/src/moaicore/MOAIBlendMode.cpp \
$(SRC_PATH)/src/moaicore/MOAIBlocker.cpp \
$(SRC_PATH)/src/moaicore/MOAIBox2DArbiter.cpp \
$(SRC_PATH)/src/moaicore/MOAIBox2DBody.cpp \
$(SRC_PATH)/src/moaicore/MOAIBox2DDebugDraw.cpp \
$(SRC_PATH)/src/moaicore/MOAIBox2DDistanceJoint.cpp \
$(SRC_PATH)/src/moaicore/MOAIBox2DFixture.cpp \
$(SRC_PATH)/src/moaicore/MOAIBox2DFrictionJoint.cpp \
$(SRC_PATH)/src/moaicore/MOAIBox2DGearJoint.cpp \
$(SRC_PATH)/src/moaicore/MOAIBox2DJoint.cpp \
$(SRC_PATH)/src/moaicore/MOAIBox2DLineJoint.cpp \
$(SRC_PATH)/src/moaicore/MOAIBox2DMouseJoint.cpp \
$(SRC_PATH)/src/moaicore/MOAIBox2DPrismaticJoint.cpp \
$(SRC_PATH)/src/moaicore/MOAIBox2DPulleyJoint.cpp \
$(SRC_PATH)/src/moaicore/MOAIBox2DRevoluteJoint.cpp \
$(SRC_PATH)/src/moaicore/MOAIBox2DWeldJoint.cpp \
$(SRC_PATH)/src/moaicore/MOAIBox2DWorld.cpp \
$(SRC_PATH)/src/moaicore/MOAIButtonSensor.cpp \
$(SRC_PATH)/src/moaicore/MOAICameraAnchor2D.cpp \
$(SRC_PATH)/src/moaicore/MOAICameraFitter2D.cpp \
$(SRC_PATH)/src/moaicore/MOAIColor.cpp \
$(SRC_PATH)/src/moaicore/MOAICompassSensor.cpp \
$(SRC_PATH)/src/moaicore/moaicore.cpp \
$(SRC_PATH)/src/moaicore/moaicore-pch.cpp \
$(SRC_PATH)/src/moaicore/MOAICp.cpp \
$(SRC_PATH)/src/moaicore/MOAICpArbiter.cpp \
$(SRC_PATH)/src/moaicore/MOAICpBody.cpp \
$(SRC_PATH)/src/moaicore/MOAICpConstraint.cpp \
$(SRC_PATH)/src/moaicore/MOAICpDebugDraw.cpp \
$(SRC_PATH)/src/moaicore/MOAICpShape.cpp \
$(SRC_PATH)/src/moaicore/MOAICpSpace.cpp \
$(SRC_PATH)/src/moaicore/MOAIDataBuffer.cpp \
$(SRC_PATH)/src/moaicore/MOAIDataIOAction.cpp \
$(SRC_PATH)/src/moaicore/MOAIDeck.cpp \
$(SRC_PATH)/src/moaicore/MOAIDeck2D.cpp \
$(SRC_PATH)/src/moaicore/MOAIDeckRemapper.cpp \
$(SRC_PATH)/src/moaicore/MOAIDebugLines.cpp \
$(SRC_PATH)/src/moaicore/MOAIDraw.cpp \
$(SRC_PATH)/src/moaicore/MOAIEaseDriver.cpp \
$(SRC_PATH)/src/moaicore/MOAIEaseType.cpp \
$(SRC_PATH)/src/moaicore/MOAIEnvironment.cpp \
$(SRC_PATH)/src/moaicore/MOAIEventSource.cpp \
$(SRC_PATH)/src/moaicore/MOAIFrameBuffer.cpp \
$(SRC_PATH)/src/moaicore/MOAIFileSystem.cpp \
$(SRC_PATH)/src/moaicore/MOAIFont.cpp \
$(SRC_PATH)/src/moaicore/MOAIFreetypeFontRipper.cpp \
$(SRC_PATH)/src/moaicore/MOAIGfxDevice.cpp \
$(SRC_PATH)/src/moaicore/MOAIGfxQuad2D.cpp \
$(SRC_PATH)/src/moaicore/MOAIGfxQuadDeck2D.cpp \
$(SRC_PATH)/src/moaicore/MOAIGfxQuadListDeck2D.cpp \
$(SRC_PATH)/src/moaicore/MOAIGfxResource.cpp \
$(SRC_PATH)/src/moaicore/MOAIGlyph.cpp \
$(SRC_PATH)/src/moaicore/MOAIGrid.cpp \
$(SRC_PATH)/src/moaicore/MOAIGridSpace.cpp \
$(SRC_PATH)/src/moaicore/MOAIHttpTask.cpp \
$(SRC_PATH)/src/moaicore/MOAIImage-jpg.cpp \
$(SRC_PATH)/src/moaicore/MOAIImage-png.cpp \
$(SRC_PATH)/src/moaicore/MOAIImage.cpp \
$(SRC_PATH)/src/moaicore/MOAIIndexBuffer.cpp \
$(SRC_PATH)/src/moaicore/MOAIInputDevice.cpp \
$(SRC_PATH)/src/moaicore/MOAIInputMgr.cpp \
$(SRC_PATH)/src/moaicore/MOAIJoystickSensor.cpp \
$(SRC_PATH)/src/moaicore/MOAIJsonParser.cpp \
$(SRC_PATH)/src/moaicore/MOAIKeyboardSensor.cpp \
$(SRC_PATH)/src/moaicore/MOAILayer2D.cpp \
$(SRC_PATH)/src/moaicore/MOAILayerBridge2D.cpp \
$(SRC_PATH)/src/moaicore/MOAILayoutFrame.cpp \
$(SRC_PATH)/src/moaicore/MOAILineBrush.cpp \
$(SRC_PATH)/src/moaicore/MOAILocationSensor.cpp \
$(SRC_PATH)/src/moaicore/MOAILogMessages.cpp \
$(SRC_PATH)/src/moaicore/MOAILogMgr.cpp \
$(SRC_PATH)/src/moaicore/MOAIMesh.cpp \
$(SRC_PATH)/src/moaicore/MOAIMotionSensor.cpp \
$(SRC_PATH)/src/moaicore/MOAINode.cpp \
$(SRC_PATH)/src/moaicore/MOAINodeMgr.cpp \
$(SRC_PATH)/src/moaicore/MOAIParser.cpp \
$(SRC_PATH)/src/moaicore/MOAIParticleDistanceEmitter.cpp \
$(SRC_PATH)/src/moaicore/MOAIParticleEmitter.cpp \
$(SRC_PATH)/src/moaicore/MOAIParticleForce.cpp \
$(SRC_PATH)/src/moaicore/MOAIParticlePlugin.cpp \
$(SRC_PATH)/src/moaicore/MOAIParticleScript.cpp \
$(SRC_PATH)/src/moaicore/MOAIParticleState.cpp \
$(SRC_PATH)/src/moaicore/MOAIParticleSystem.cpp \
$(SRC_PATH)/src/moaicore/MOAIParticleTimedEmitter.cpp \
$(SRC_PATH)/src/moaicore/MOAIPartition.cpp \
$(SRC_PATH)/src/moaicore/MOAIPartitionCell.cpp \
$(SRC_PATH)/src/moaicore/MOAIPartitionLayer.cpp \
$(SRC_PATH)/src/moaicore/MOAIPartitionResultBuffer.cpp \
$(SRC_PATH)/src/moaicore/MOAIPartitionResultMgr.cpp \
$(SRC_PATH)/src/moaicore/MOAIPointerSensor.cpp \
$(SRC_PATH)/src/moaicore/MOAIProp.cpp \
$(SRC_PATH)/src/moaicore/MOAIProp2D.cpp \
$(SRC_PATH)/src/moaicore/MOAIQuadBrush.cpp \
$(SRC_PATH)/src/moaicore/MOAIScriptDeck.cpp \
$(SRC_PATH)/src/moaicore/MOAIScriptNode.cpp \
$(SRC_PATH)/src/moaicore/MOAISensor.cpp \
$(SRC_PATH)/src/moaicore/MOAISerializer.cpp \
$(SRC_PATH)/src/moaicore/MOAIShader.cpp \
$(SRC_PATH)/src/moaicore/MOAIShaderMgr.cpp \
$(SRC_PATH)/src/moaicore/MOAISim.cpp \
$(SRC_PATH)/src/moaicore/MOAIStretchPatch2D.cpp \
$(SRC_PATH)/src/moaicore/MOAISurfaceDeck2D.cpp \
$(SRC_PATH)/src/moaicore/MOAISurfaceSampler2D.cpp \
$(SRC_PATH)/src/moaicore/MOAITextBox.cpp \
$(SRC_PATH)/src/moaicore/MOAITextFrame.cpp \
$(SRC_PATH)/src/moaicore/MOAITextLayout.cpp \
$(SRC_PATH)/src/moaicore/MOAITexture.cpp \
$(SRC_PATH)/src/moaicore/MOAIThread.cpp \
$(SRC_PATH)/src/moaicore/MOAITileDeck2D.cpp \
$(SRC_PATH)/src/moaicore/MOAITileFlags.cpp \
$(SRC_PATH)/src/moaicore/MOAITimer.cpp \
$(SRC_PATH)/src/moaicore/MOAITouchSensor.cpp \
$(SRC_PATH)/src/moaicore/MOAITraits.cpp \
$(SRC_PATH)/src/moaicore/MOAITransform.cpp \
$(SRC_PATH)/src/moaicore/MOAITransformBase.cpp \
$(SRC_PATH)/src/moaicore/MOAIVertexBuffer.cpp \
$(SRC_PATH)/src/moaicore/MOAIVertexFormat.cpp \
$(SRC_PATH)/src/moaicore/MOAIVertexFormatMgr.cpp \
$(SRC_PATH)/src/moaicore/MOAIViewport.cpp \
$(SRC_PATH)/src/moaicore/MOAIXmlParser.cpp

include $(BUILD_STATIC_LIBRARY)