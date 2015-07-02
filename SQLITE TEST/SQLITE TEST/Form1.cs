using System;
using Finisar.SQLite;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace SQLITE_TEST
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            button2.Visible = false;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            button2.Visible = true;
            // We use these three SQLite objects:
            SQLiteConnection sqlite_conn;
            SQLiteCommand sqlite_cmd;
            SQLiteDataReader sqlite_datareader;

            // create a new database connection:
            sqlite_conn = new SQLiteConnection("Data Source=database.db;Version=3;New=False;Compress=True;");

            // open the connection:
            sqlite_conn.Open();

            // create a new SQL command:
            sqlite_cmd = sqlite_conn.CreateCommand();
            try
            {

                // Let the SQLiteCommand object know our SQL-Query:
                sqlite_cmd.CommandText = "CREATE TABLE EMPLOYEE (EMP_ID varchar(20) PRIMARY KEY, EMP_NAME varchar(20) NOT NULL, JOB_TITLE varchar(20) NOT NULL);";

                // Now lets execute the SQL ;D
                //try
                sqlite_cmd.ExecuteNonQuery();
            }
            catch (SQLiteException e1)
            {
                sqlite_cmd.CommandText = "DELETE FROM EMPLOYEE";
                sqlite_cmd.ExecuteNonQuery();

            }

            finally
            {
                try
                {
                    // Lets insert something into our new table:
                    sqlite_cmd.CommandText = "INSERT INTO EMPLOYEE VALUES (2210311146, 'MONISH', 'DBA');";

                    // And execute this again ;D
                    sqlite_cmd.ExecuteNonQuery();

                    // ...and inserting another line:
                    sqlite_cmd.CommandText = "INSERT INTO EMPLOYEE VALUES (2210311130, 'VARSHA', 'DBA');";

                    // And execute this again ;D
                    sqlite_cmd.ExecuteNonQuery();

                    // But how do we read something out of our table ?
                    // First lets build a SQL-Query again:
                    sqlite_cmd.CommandText = "SELECT * FROM EMPLOYEE;";

                    // Now the SQLiteCommand object can give us a DataReader-Object:
                    sqlite_datareader = sqlite_cmd.ExecuteReader();

                    DataTable dt = new DataTable();                                //CODE TO DISPLAY DATA ON A GRIDVIEW.
                    SQLiteDataAdapter adp = new SQLiteDataAdapter(sqlite_cmd);
                    adp.Fill(dt);
                    dataGridView1.DataSource = dt;
                    adp.Update(dt);
                    sqlite_conn.Close();
                }
                catch (SQLiteException se)
                {
                    MessageBox.Show((se.ToString()));
                }
            }

        }

        private void button2_Click(object sender, EventArgs e)
        {
            int temp_rows=0;
            String update_value = "";
            SQLiteConnection sqlite_conn;
            SQLiteCommand sqlite_cmd;
            DataTable dt = new DataTable();

            // create a new database connection:
            sqlite_conn = new SQLiteConnection("Data Source=database.db;Version=3;New=False;Compress=True;");

            // open the connection:
            sqlite_conn.Open();
            sqlite_cmd = sqlite_conn.CreateCommand();
            sqlite_cmd.CommandText = "DELETE FROM EMPLOYEE;";
            sqlite_cmd.ExecuteNonQuery();
            dataGridView1.CommitEdit(DataGridViewDataErrorContexts.Commit);

            for (temp_rows = 0; temp_rows < dataGridView1.Rows.Count-1;temp_rows++)
            {
                DataGridViewRow dr = dataGridView1.Rows[temp_rows];
                DataRow de = (dr.DataBoundItem as DataRowView).Row;
                foreach (object obj in de.ItemArray)
                {
                    update_value = update_value +"'"+obj.ToString()+"'" + ",";
                }
                sqlite_cmd.CommandText = "INSERT INTO EMPLOYEE VALUES(" + update_value.Remove(update_value.Length - 1).Trim() + ");";
                sqlite_cmd.ExecuteNonQuery();
                update_value = "";
            }
                MessageBox.Show("DATA UPDATED SUCCESFULLY", "UPDATE", MessageBoxButtons.OK, MessageBoxIcon.Information);
                sqlite_conn.Close();
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }
    }
}
