from fastapi import FastAPI, Depends, HTTPException
from sqlalchemy.orm import Session
from . import models, schemas, database

app = FastAPI()

# Dependency
def get_db():
    db = database.SessionLocal()
    try:
        yield db
    finally:
        db.close()

@app.post("/hospitals/", response_model=schemas.Hospital)
def create_hospital(hospital: schemas.HospitalCreate, db: Session = Depends(get_db)):
    db_hospital = models.Hospital(**hospital.dict())
    db.add(db_hospital)
    db.commit()
    db.refresh(db_hospital)
    return db_hospital

@app.get("/hospitals/{hospital_id}", response_model=schemas.Hospital)
def read_hospital(hospital_id: int, db: Session = Depends(get_db)):
    db_hospital = db.query(models.Hospital).filter(models.Hospital.id == hospital_id).first()
    if db_hospital is None:
        raise HTTPException(status_code=404, detail="Hospital not found")
    return db_hospital