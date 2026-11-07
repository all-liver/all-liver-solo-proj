import { useEffect, useState } from 'react'
import { type User, type Userwpassword } from './type';

//need major overhaul all after you write the update page

function accDisp(acc: User, 
    callback: (act: string) => void,
    setViewingAcc: () => void,
    setProfile: (pro: User) => void) {
    const format = [
        "name",
        "email",
        "birthday",
        "department",
        "yearJoined"
    ] as Array<keyof User>
    return (
        <tr>
            {format.map(ky => {
                const value = acc[ky];
                return <td key={ky}>{value instanceof Date ? value.toLocaleDateString() : value}</td>;
            })}
            {/*make the buttons jump to a new page with that function*/}
            <td className="staff-action-column-2">
                <button type="button" className="staff-manage-button-2" onClick={() => {
                    callback("PATCH")
                    setProfile(acc)
                    setViewingAcc()
                }}>
                    Manage
                </button>
            </td>
        </tr>
    )
}

type ListpageProps = {
    setViewingAcc: () => void
    setAction: (act: string) => void
    setProfile: (acc: User) => void
};

export default function Listpage({ setViewingAcc, setAction, setProfile }: ListpageProps) {
    const [users, setUsers] = useState<Userwpassword[]>();
    const [loading, setLoading] = useState(true);
    const [error, setError] = useState<string | null>(null);

    useEffect(() => {
        const controller = new AbortController();

        async function loadUsers() {
            try {
                const response = await fetch(`/api/users`, {
                    headers: {
                        'Content-Type': 'application/json'
                    },
                    method: "GET",
                    signal: controller.signal,
                });

                if (!response.ok) {
                    throw new Error(`Could not load users (HTTP ${response.status})`);
                }

                const data: Userwpassword[] = await response.json();
                setUsers(data);
            } catch (err) {
                if (!controller.signal.aborted) {
                    setError(err instanceof Error ? err.message : 'Could not load users');
                }
            } finally {
                if (!controller.signal.aborted) {
                    setLoading(false);
                }
            }
        }
        loadUsers()

        return () => controller.abort()
    }, [])
    if (loading) {
        return <main className="placeholder">Loading accounts…</main>;
    }

    if (error) {
        return <main className="placeholder">Could not load accounts: {error}</main>;
    }

    if (!users || users.length === 0) {
        return <main className="placeholder">No accounts found.</main>;
    }

    return (
        <div className="staff-table-wrap">
            <table className="staff-table">
              <thead>
                <tr>
                  <th scope="col">Name</th>
                  <th scope="col">Email</th>
                  <th scope="col">Department</th>
                  <th scope="col">Role</th>
                  <th scope="col" className="staff-action-column-2">
                    Action
                  </th>
                </tr>
              </thead>
              <tbody>
                {users?.map((acc: User) => accDisp(acc, 
                        setAction, setViewingAcc, setProfile))}
                
              </tbody>
            </table>
          </div>
    )
}