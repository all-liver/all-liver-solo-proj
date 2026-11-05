import { useState } from 'react'
import './StaffScreen.css'

const staffAccounts = [
  { name: 'Alice Wong', email: 'alice.wong@worksmartse.com' },
  { name: 'Ben Chan', email: 'ben.chan@worksmartse.com' },
  { name: 'Cara Lee', email: 'cara.lee@worksmartse.com' },
  { name: 'Dan Ho', email: 'dan.ho@worksmartse.com' },
  { name: 'Eve Ng', email: 'eve.ng@worksmartse.com' },
  { name: 'Marco Tsang', email: 'marco.tsang@worksmartse.com' },
]

function StaffScreen() {
  const [isCreateDialogOpen, setIsCreateDialogOpen] = useState(true)

  return (
    <main className="staff-screen">
      <header className="staff-header">
        <a className="staff-brand" href="#" aria-label="LeaveFlowSE home">
          LeaveFlowSE
        </a>

        <nav className="staff-nav" aria-label="Main navigation">
          <a href="#">Dashboard</a>
          <a href="#">Approvals</a>
          <a href="#">Leave records</a>
          <a className="staff-nav-active" href="#" aria-current="page">
            Accounts
          </a>
        </nav>

        <div className="staff-user">
          <span>Wai Ting - Approver</span>
          <button type="button" className="staff-sign-out">
            Sign out
          </button>
        </div>
      </header>

      <section className="staff-content" aria-labelledby="accounts-title">
        <div className="staff-page-heading">
          <div>
            <h1 id="accounts-title">Accounts</h1>
            <p className="staff-date">Tuesday, 3 November 2028</p>
          </div>
          <button
            type="button"
            className="staff-button staff-button-primary"
            onClick={() => setIsCreateDialogOpen(true)}
          >
            Create account
          </button>
        </div>

        <section className="staff-card" aria-labelledby="staff-accounts-title">
          <div className="staff-card-heading">
            <h2 id="staff-accounts-title">Staff accounts</h2>
            <p>6 active accounts at WorkSmartSE.</p>
          </div>

          <div className="staff-table-wrap">
            <table className="staff-table">
              <thead>
                <tr>
                  <th scope="col">Name</th>
                  <th scope="col">Email</th>
                  <th scope="col" className="staff-action-column">
                    Action
                  </th>
                </tr>
              </thead>
              <tbody>
                {staffAccounts.map((account) => (
                  <tr key={account.email}>
                    <td>{account.name}</td>
                    <td>{account.email}</td>
                    <td className="staff-action-column">
                      <button type="button" className="staff-manage-button">
                        Manage
                      </button>
                    </td>
                  </tr>
                ))}
              </tbody>
            </table>
          </div>
        </section>
      </section>

      {isCreateDialogOpen && (
        <div className="staff-dialog-backdrop">
          <section
            className="staff-dialog"
            role="dialog"
            aria-modal="true"
            aria-labelledby="create-account-title"
            aria-describedby="create-account-description"
          >
            <div className="staff-dialog-heading">
              <div>
                <h2 id="create-account-title">Create account</h2>
                <p id="create-account-description">
                  Add a WorkSmartSE staff account.
                </p>
              </div>
              <button
                type="button"
                className="staff-close-button"
                aria-label="Close"
                onClick={() => setIsCreateDialogOpen(false)}
              >
                ×
              </button>
            </div>

            <form className="staff-form">
              <label className="staff-field">
                <span>Full name</span>
                <input type="text" defaultValue="Grace Lau" />
              </label>

              <label className="staff-field">
                <span>Work email</span>
                <input
                  type="email"
                  defaultValue="grace.lau@worksmartse.com"
                  aria-describedby="work-email-hint"
                />
                <span className="staff-field-hint" id="work-email-hint">
                  Must use the worksmartse.com domain.
                </span>
              </label>

              <div className="staff-field-row">
                <label className="staff-field">
                  <span>Department</span>
                  <select defaultValue="Sales">
                    <option>Sales</option>
                  </select>
                </label>
                <label className="staff-field">
                  <span>Role</span>
                  <select defaultValue="Staff">
                    <option>Staff</option>
                  </select>
                </label>
              </div>

              <div className="staff-dialog-actions">
                <button
                  type="button"
                  className="staff-button staff-button-secondary"
                  onClick={() => setIsCreateDialogOpen(false)}
                >
                  Cancel
                </button>
                <button type="button" className="staff-button staff-button-primary">
                  Create account
                </button>
              </div>
            </form>
          </section>
        </div>
      )}
    </main>
  )
}

export default StaffScreen
