import { useState } from "react";
import Listpage from './listpage'
import Inputslot from './inputmodule'
import type { User, Userwpassword } from './type'
import './src/listpage2.css'

//name the suitable function later. you got time.

export default function demoUI() {
    const [viewingAcc, setViewingAcc] = useState(true)
    const [action, setAction] = useState<string>("POST")
    const [profile, setProfile] = useState<User>()

    return (
        <main className="staff-screen-2">
            <header className="staff-header-2">
                <a className="staff-brand-2" href="#" aria-label="LeaveFlowSE home">
                    LeaveFlowSE
                </a>

                <nav className="staff-nav-2" aria-label="Main navigation">
                    <a href="#">Dashboard</a>
                    <a href="#">Approvals</a>
                    <a href="#">Leave records</a>
                    <a className="staff-nav-active-2" href="#" aria-current="page">
                        Accounts
                    </a>
                </nav>

                <div className="staff-user-2">
                    <span>Wai Ting - Approver</span>
                    <button type="button" className="staff-sign-out-2">
                        Sign out
                    </button>
                </div>
            </header>

            <section className="staff-content-2" aria-labelledby="accounts-title-2">
                <div className="staff-page-heading-2">
                    <div>
                        <h1 id="accounts-title-2">Accounts</h1>
                        <p className="staff-date-2">Tuesday, 3 November 2028</p>
                    </div>
                    <button type="button" className="staff-create-button-2">
                        Create account
                    </button>
                </div>

                <section className="staff-card" aria-labelledby="staff-accounts-title-2">
                    <div className="staff-card-heading">
                        <h2 id="staff-accounts-title-2">Staff accounts</h2>
                        <p>6 active accounts at WorkSmartSE.</p>
                    </div>
                    {(viewingAcc)?(
                    <Listpage
                        setViewingAcc={() => setViewingAcc(false)}
                        setAction={setAction}
                        setProfile={setProfile}
                    />
                    ):(
                    <Inputslot
                        setViewingAcc={() => setViewingAcc(true)}
                        Profile={profile}
                        Action={action}
                    />
                    )}
                </section>
            </section>
        </main>
    )
}
