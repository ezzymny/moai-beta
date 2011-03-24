print ( "hello, moai!" )

scene = MOAILayer2D.new ()

viewport = MOAIViewport.new ()
viewport:setSize ( 320, 480 )
viewport:setScale ( 320, 480 )

scene:setViewport ( viewport )
MOAISim.pushRenderPass ( scene )

sprite = MOAISprite2D.new ()

texture = MOAITexture.new ()
texture:load ( "cathead.png" )
texture:setRect ( -64, -64, 64, 64 )

sprite:setGfxSource ( texture )

partition = MOAIPartition.new ()
partition:insertPrim ( sprite )
scene:setPartition ( partition )

thread = MOAIThread.new ()
 
function threadFunc ( x, y )
 
	print ( x )
	print ( y )
 
    local action
 
    action = sprite:moveRot ( 180, 3 )
    MOAIThread.blockOnAction ( action )
 
    action = sprite:moveLoc ( 64, 0, 2 ) 
    MOAIThread.blockOnAction ( action )
 
    action = sprite:moveScl ( -0.5, -0.5, 1 ) 
    MOAIThread.blockOnAction ( action )

	action = sprite:moveRot ( -180, 3 )
    MOAIThread.blockOnAction ( action )
	
end

thread:run ( threadFunc, "foo", "bar" )

MOAISim.openWindow ( "cathead", 320, 480 )