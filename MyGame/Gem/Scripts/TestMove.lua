--local utilities = require "scripts/common/utilities"
--local StateMachine = require "scripts/common/StateMachine"

local MathUtil = require "scripts/utils/math"

local TestMove =
{
	Properties =
	{
		EventName = { default = "EventName", description = "Name of the event to trigger the movement." },
		Target = { default = EntityId() },
		
		NewPosition =
		{
			PositionOffset = { default = Vector3(0.0, 0.0, 0.0), description = "When triggered, move the entity to this position relative to it's parent" },
			Duration = { default = 1.0, description = "When triggered, take this long to move the entity to it's new position" },
		},
		
		LerpType =
		{
			Linear = { default = true },
			Exponential = { default = false },
		},
	},
}

function TestMove:OnActivate()

	self.triggerEventId = GameplayNotificationId(self.entityId, self.Properties.EventName, "float");
	self.triggerHandler = GameplayNotificationBus.Connect(self, self.triggerEventId);
	
	self.tickHandler = TickBus.Connect(self);
	self.performedFirstUpdate = false;
	
	if (not self.Properties.Target:IsValid()) then
		self.Properties.Target = self.entityId;
	end
	
	self.isMoving = false;
	self.originalTM = nil;
	
	
	--Debug.Log("Target pos: " .. tostring(self.targetPos));
	
	
	self.isMoving = true;
	self.timeSpent = 0.0;
	--self.originalTM = TransformBus.Event.GetLocalTM(self.Properties.Target);
	
	local tm = TransformBus.Event.GetLocalTM(self.entityId);
	self.targetPos = tm:GetTranslation() + self.Properties.NewPosition.PositionOffset; 
	
	self.originalPos = tm:GetTranslation();

end

function TestMove:OnDeactivate()

	if (self.tickHandler ~= nil) then
		self.tickHandler:Disconnect();
		self.tickHandler = nil;
	end

	if (self.triggerHandler ~= nil) then
		self.triggerHandler:Disconnect();
		self.triggerHandler = nil;
	end

end

function TestMove:OnTick(deltaTime, timePoint)

	if (self.performedFirstUpdate == false) then
		self.performedFirstUpdate = true;
	end
	
	--local tm = TransformBus.Event.GetLocalTM(self.Properties.Target);
	local tm = TransformBus.Event.GetLocalTM(self.entityId);
	local newPos = tm:GetTranslation();
	self.timeSpent = self.timeSpent + deltaTime;
	
	
	local t = math.sin(self.timeSpent * self.Properties.NewPosition.Duration);
	local offset = self.Properties.NewPosition.PositionOffset;
	
	offset = offset * t;
	newPos = self.originalPos + offset;
	
-- 		
-- 	if (self.timeSpent >= self.Properties.NewPosition.Duration) then
-- 		--newPos = tm:GetTranslation();
-- 		--self.isMoving = false;
-- 		
-- 		newPos = self.originalPos;
-- 		self.timeSpent = 0.0;
-- 	else
-- 		local t = self.timeSpent / self.Properties.NewPosition.Duration;
-- 		newPos = self:LerpThis(tm:GetTranslation(), self.targetPos, t);
-- 	end
	
	tm:SetTranslation(newPos);
	--tm:SetTranslation(newPos);
	--Debug.Log("New position: " .. tostring(newPos));
	--TransformBus.Event.SetLocalTM(self.Properties.Target, tm);
	TransformBus.Event.SetLocalTM(self.entityId, tm);

end

-- s == start
-- e == end
-- l == lerp
-- This function expects 's' and 'e' to be 'Vector3's.
function TestMove:LerpThis(s, e, l)

	local ret;
	if (self.Properties.LerpType.Linear == true) then
		ret = s:Lerp(e, l);
	elseif (self.Properties.LerpType.Exponential == true) then
		ret = s:Lerp(e, l * l);
	else
		Debug.Assert("Unspecified lerp type.");
	end
	
	return ret;

end

function TestMove:OnEventBegin(value)

	if (GameplayNotificationBus.GetCurrentBusId() == self.triggerEventId) then
		self.isMoving = true;
		self.timeSpent = 0.0;
		--self.originalTM = TransformBus.Event.GetLocalTM(self.Properties.Target);
		--Debug.Log("Moving");
	end

end

return TestMove;