from sqlalchemy import Column, Integer, String, DateTime
from .database import Base

class Document(Base):
    __tablename__ = "documents"

    id = Column(Integer, primary_key=True, index=True)
    patient_id = Column(Integer, index=True)
    hospital_id = Column(Integer, index=True)
    visit_date = Column(DateTime)
    notes = Column(String)