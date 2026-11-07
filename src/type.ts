import { type UserModel } from './prisma/models.ts'

export type User = Omit <Userwpassword,'passwordHash'>
export type Userwpassword=UserModel