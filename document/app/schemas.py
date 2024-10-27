from pydantic import BaseModel
from datetime import datetime

class DocumentBase(BaseModel):
    patient_id: int
    hospital_id: int
    visit_date: datetime
    notes: str

class DocumentCreate(DocumentBase):
    pass

class Document(DocumentBase):
    id: int

    class Config:
        orm_mode = True