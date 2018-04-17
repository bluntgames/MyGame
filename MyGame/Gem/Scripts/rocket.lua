local rocket =
{
    Properties =
    {
        InitialVelocity = {default=Vector3(), description="The initial speed and direction of the entity"},
        Impulse = {default=Vector3(), description="The impulse to add every frame"},
    },
}
  
function rocket:OnActivate()
    PhysicsComponentRequestBus.Event.SetVelocity(self.entityId, self.Properties.InitialVelocity)
    --self.TickHandler = TickBus.CreateHandler(self)
	
	self.triggerEventId = GameplayNotificationId(self.entityId, self.Properties.EventName, "float");
	self.triggerHandler = GameplayNotificationBus.Connect(self, self.triggerEventId);
	
	self.tickHandler = TickBus.Connect(self);

end
  
function rocket:OnTick(deltaTime, timePoint)
    PhysicsComponentRequestBus.Event.AddImpulse(self.entityId, self.Properties.Impulse)
end
  
function rocket:OnDeactivate()
    self.tickHandler:Disconnect()
end
  
return rocket