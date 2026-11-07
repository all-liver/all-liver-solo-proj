import { useState, useEffect } from 'react'
import type { User, Userwpassword } from './type'

type newUser = Omit<Userwpassword, 'id'>

const knit = () => {
    let acc = {} as newUser
    let input: any
    input = document.getElementById("staffId")
    if (input instanceof HTMLInputElement) acc.staffId = input.value
    input = document.getElementById("email")
    if (input instanceof HTMLInputElement) acc.email = input.value
    input = document.getElementById("birthday")
    if (input instanceof HTMLInputElement) acc.birthday = input.value
    input = document.getElementById("name")
    if (input instanceof HTMLInputElement) acc.name = input.value
    input = document.getElementById("department")
    if (input instanceof HTMLInputElement) acc.department = input.value
    input = document.getElementById("passwordHash")
    if (input instanceof HTMLInputElement) acc.passwordHash = input.value
    input = document.getElementById("yearJoined")
    if (input instanceof HTMLInputElement) acc.yearJoined = input.valueAsNumber
    return acc
}

type Inputslot = {
    setViewingAcc: () => void;
    Profile?: User
    Action: string;
};

export default function inputslot({ setViewingAcc, Profile, Action }: Inputslot) {
    const format = [
        { key: "name", lb: "Name" },
        { key: "email", lb: "Email" },
        { key: "staffId", lb: "Staff ID" },
        { key: "birthday", lb: "Birthday" },
        { key: "department", lb: "Department" },
        { key: "yearJoined", lb: "Year joined" },
        { key: "passwordHash", lb: "Password" },
    ] as const satisfies readonly { key: keyof Userwpassword; lb: string }[];
    const fact = (async (p: Object, m: string) => await fetch('/api/users', {
        headers: { 'Content-Type': 'application/json' },
        method: m,
        body: JSON.stringify(p)
    }))
    async function submit() {
        const prof: newUser = knit()
        const fullprof = (Action === "POST") ? prof : { ...prof, id: Profile?.id }
        const response = await fact(fullprof, Action)
        if (!response.ok) {
            throw new Error(`Could not create user (HTTP ${response.status})`);
        }
        setViewingAcc()
    }
    const [v, f] = useState<newUser>()
    async function internalchecking() {
        f(knit())
    }

    return (
        <div className="placeholderclass">
            {format.map(({ key, lb }) => (
                <label>
                    <h1>{lb} : </h1>
                    <input id={key} type={(key === "yearJoined") ? "number" : "text"} />
                </label>
            ))}
            <button onClick={submit}>Submit</button>
            <button onClick={internalchecking}>internal</button>
            <p>${v ? JSON.stringify(v) : 'No form data yet'}</p>
        </div>
    )
}

//Listen here
//this file put the button into the same body part of the input slots, so you may need to fix that part
//I hope we don't need to fix that part