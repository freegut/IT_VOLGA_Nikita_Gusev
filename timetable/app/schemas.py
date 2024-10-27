from pydantic import BaseModel
from datetime import datetime

class AppointmentBase(BaseModel):
    doctor_id: int
    hospital_id: int
    patient_id: int
    appointment_time: datetime

class AppointmentCreate(AppointmentBase):
    pass

class Appointment(AppointmentBase):
    id: int

    class Config:
        orm_mode = True