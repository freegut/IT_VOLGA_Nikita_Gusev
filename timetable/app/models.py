from sqlalchemy import Column, Integer, String, DateTime
from .database import Base

class Appointment(Base):
    __tablename__ = "appointments"

    id = Column(Integer, primary_key=True, index=True)
    doctor_id = Column(Integer, index=True)
    hospital_id = Column(Integer, index=True)
    patient_id = Column(Integer, index=True)
    appointment_time = Column(DateTime)