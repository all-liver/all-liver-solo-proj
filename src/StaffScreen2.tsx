import './StaffScreen2.css'

const staffAccounts = [
  {
    name: 'Alice Wong',
    email: 'alice.wong@worksmartse.com',
    department: 'Sales',
    role: 'Staff',
  },
  {
    name: 'Ben Chan',
    email: 'ben.chan@worksmartse.com',
    department: 'Marketing',
    role: 'Staff',
  },
  {
    name: 'Cara Lee',
    email: 'cara.lee@worksmartse.com',
    department: 'Operations',
    role: 'Staff',
  },
  {
    name: 'Dan Ho',
    email: 'dan.ho@worksmartse.com',
    department: 'Finance',
    role: 'Staff',
  },
  {
    name: 'Eve Ng',
    email: 'eve.ng@worksmartse.com',
    department: 'Support',
    role: 'Staff',
  },
  {
    name: 'Marco Tsang',
    email: 'marco.tsang@worksmartse.com',
    department: 'IT',
    role: 'Approver',
  },
]

function StaffScreen2() {
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

        <section className="staff-card-2" aria-labelledby="staff-accounts-title-2">
          <div className="staff-card-heading-2">
            <h2 id="staff-accounts-title-2">Staff accounts</h2>
            <p>6 active accounts at WorkSmartSE.</p>
          </div>

          <div className="staff-table-wrap-2">
            <table className="staff-table-2">
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
                {staffAccounts.map((account) => (
                  <tr key={account.email}>
                    <td>{account.name}</td>
                    <td>{account.email}</td>
                    <td>{account.department}</td>
                    <td>{account.role}</td>
                    <td className="staff-action-column-2">
                      <button type="button" className="staff-manage-button-2">
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
    </main>
  )
}

export default StaffScreen2
