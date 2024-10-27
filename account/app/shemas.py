from pydantic import BaseModel

class User(BaseModel):
    username: str
    role: str

    class Config:
        orm_mode = True

class Token(BaseModel):
    access_token: str
    token_type: str