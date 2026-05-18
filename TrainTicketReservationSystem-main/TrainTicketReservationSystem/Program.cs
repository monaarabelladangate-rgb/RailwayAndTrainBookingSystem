using System;
using System.Collections.Generic;
public static class ToLogin
{
    private static string userPhone = "2243081";
    private static string userPassword = "jerin";

    public static bool Login()
    {
        Console.Write("Enter Phone Number: ");
        string phone = Console.ReadLine();

        Console.Write("Enter Password: ");
        string pass = Console.ReadLine();

        if (phone == userPhone && pass == userPassword)
        {
            Console.WriteLine("Login Successful!\n");
            return true;
        }
        else
        {
            return false;
        }
    }
}




// interface
public interface TrainA
{
    void Display(string message);
}
public interface TrainB
{
    void DisplayTrain();
}
class Train : TrainA, TrainB
{
    private int trainNumber;
    private string trainName;
    private string from;
    private string to;
    private int totalSeat;
    private int availableSeat;

    public int TrainNumber
    {
        get { return trainNumber; }
        set { trainNumber = value; }
    }
    public string TrainName
    {
        get { return trainName; }
        set { trainName = value; }
    }
    public string From
    {
        get { return from; }
        set { from = value; }
    }
    public string To
    {
        get { return to; }
        set { to = value; }
    }
    public int TotalSeat
    {
        get { return totalSeat; }
        set { totalSeat = value; }
    }
    public int AvailableSeat
    {
        get { return availableSeat; }
        set { availableSeat = value; }
    }

    // Default Constructor
    public Train()
    {
        trainNumber = 0;
        trainName = "Unknown";
        from = "Unknown";
        to = "Unknown";
        totalSeat = 0;
        availableSeat = 0;
    }

    // Main Constructor
    public Train(int num, string name, string from, string to, int total, int available)
    {
        trainNumber = num;
        trainName = name;
        this.from = from;
        this.to = to;
        totalSeat = total;
        availableSeat = available;
    }

    // Copy Constructor
    public Train(Train t)
    {
        trainNumber = t.trainNumber;
        trainName = t.trainName;
        from = t.from;
        to = t.to;
        totalSeat = t.totalSeat;
        availableSeat = t.availableSeat;
    }

    public void Display(string message)
    {
        Console.WriteLine(message);
    }
    public void DisplayTrain()
    {
        Console.WriteLine($"{trainNumber,-12}{trainName,-20}{from,-15}{to,-15}{availableSeat}/{totalSeat}");
    }

    // increment n decrement seats using operator overloading
    public static Train operator ++(Train t)
    {
        t.availableSeat++; // increment available seats by 1
        return t;
    }

    public static Train operator --(Train t)
    {
        if (t.availableSeat > 0)
            t.availableSeat--; // decrement available seats by 1
        return t;
    }
}




// class for inheritance
public class TicketBase
{
    private int ticketId;
    private string passengerName;
    private int trainNumber;
    private string _class;
    private bool cancelled;

    public int TicketId
    {
        get { return ticketId; }
        set { ticketId = value; }
    }
    public string PassengerName
    {
        get { return passengerName; }
        set { passengerName = value; }
    }
    public int TrainNumber
    {
        get { return trainNumber; }
        set { trainNumber = value; }
    }
    public string Class
    {
        get { return _class; }
        set { _class = value; }
    }
    public bool Cancelled
    {
        get { return cancelled; }
        set { cancelled = value; }
    }

    public TicketBase(int id, string name, int tnum, string _class)
    {
        ticketId = id;
        passengerName = name;
        trainNumber = tnum;
        this._class = _class;
        cancelled = false;
    }
    public virtual void DisplayTicket()
    {

    }
}
class Ticket : TicketBase
{
    public Ticket(int id, string name, int tnum, string _class) : base(id, name, tnum, _class)
    {

    }

    public override void DisplayTicket()
    {
        if (!Cancelled)
            Console.WriteLine($"{TicketId,-10} {PassengerName,-20} {TrainNumber,-20} {Class,-20}");
    }
}




// abstract class
public abstract class TrainReservationSystemBase
{
    public abstract void ViewTrains();
    public abstract void BookTicket();
    public abstract void ViewBooked();
    public abstract void CancelTicket();
}
class TrainReservationSystem : TrainReservationSystemBase
{
    private List<Train> trains = new List<Train>();
    private List<Ticket> tickets = new List<Ticket>();
    private int ticketCounter = 1;

    // CONSTRUCTOR -> Add 6 trains 
    public TrainReservationSystem()
    {
        // Train 1
        Train t1 = new Train(101, "Subarna Express", "Dhaka", "Mymensingh", 5, 5);
        trains.Add(t1);
        // Train 2
        Train t2 = new Train(202, "Turna Express", "Dhaka", "Chittagong", 3, 3);
        trains.Add(t2);
        // Train 3
        Train t3 = new Train(303, "Paharica Express", "Sylhet", "Chittagong", 4, 4);
        trains.Add(t3);
        // Train 4
        Train t4 = new Train(404, "Sundarban Express", "Mymensingh", "Dhaka", 6, 6);
        trains.Add(t4);
        // Train 5
        Train t5 = new Train(505, "Simanta Express", "Mymensingh", "Chittagong", 5, 5);
        trains.Add(t5);
        // Train 6
        Train t6 = new Train(506, "Simanta Express", "Dhaka", "Khulna", 5, 5);
        trains.Add(t6);

    }

    // View All Trains
    public override void ViewTrains()
    {
        Console.WriteLine("\nTrain No.   Name                 From           To             Seats");
        Console.WriteLine("-----------------------------------------------------------------------");

        foreach (var t in trains)
        {
            t.DisplayTrain();
        }
    }

    // FARE CALCULATION (Method Overloading)
    public int CalculateFare(string from, string to)
    {
        from = from.ToLower();
        to = to.ToLower();
        if (from == "dhaka" && to == "chittagong") return 500;
        if (from == "dhaka" && to == "mymensingh") return 300;
        if (from == "sylhet" && to == "chittagong") return 450;
        if (from == "dhaka" && to == "khulna") return 550;
        return 400; // default
    }

    public int CalculateFare(string from, string to, string classType)
    {
        int baseFare = CalculateFare(from, to);
        switch (classType)
        {
            case "AC": return baseFare + 300;
            case "F_SEAT": return baseFare + 200;
            case "S_CHAIR": return baseFare + 150;
            case "SHOVAN": return baseFare + 0;
            default: return baseFare;
        }
    }

    // Book Ticket
    public override void BookTicket()
    {
        Console.Write("From: ");
        string from = Console.ReadLine().ToLower();

        Console.Write("To: ");
        string to = Console.ReadLine().ToLower();

        // Ask for travel date with validation
        DateTime travelDate;
        while (true)
        {
            Console.Write("Enter Travel Date (yyyy-MM-dd): ");
            string dateInput = Console.ReadLine();

            try
            {
                //travelDate = DateTime.Parse(dateInput);
                travelDate = Convert.ToDateTime(dateInput);

                if (travelDate.Date >= DateTime.Today)
                {
                    break; // valid date
                }
                else
                {
                    Console.WriteLine("You cannot select a past date. Please enter today or a future date.");
                }
            }
            catch (FormatException)
            {
                Console.WriteLine("Invalid date format! Please use yyyy-MM-dd.");
            }
            finally
            {
                Console.WriteLine();
            }
        }

        Console.WriteLine("\nAvailable Trains:");
        Console.WriteLine("Train No.   Name                 From           To             Seats");
        Console.WriteLine("-----------------------------------------------------------------------");

        // finding trains
        List<Train> foundTrains = new List<Train>();
        foreach (Train t in trains)
        {
            if (t.From.ToLower() == from && t.To.ToLower() == to)
            {
                t.DisplayTrain();
                foundTrains.Add(t);
            }
        }

        if (foundTrains.Count == 0)
        {
            Console.WriteLine("No trains found!");
            return;
        }

        Console.Write("Enter Train Number to Book: ");
        int trainNumber = Convert.ToInt32(Console.ReadLine());

        // Find the selected train manually
        Train selectedTrain = null;
        foreach (Train t in trains)
        {
            if (t.TrainNumber == trainNumber)
            {
                selectedTrain = t;
                break;
            }
        }

        if (selectedTrain == null)
        {
            Console.WriteLine("Train Not Found!");
            return;
        }

        if (selectedTrain.AvailableSeat == 0)
        {
            Console.WriteLine("No Seats Available!");
            return;
        }

        Console.Write("Passenger Name: ");
        string name = Console.ReadLine();

        Console.WriteLine("Choose Class:");
        Console.WriteLine("1. AC");
        Console.WriteLine("2. F_SEAT");
        Console.WriteLine("3. S_CHAIR");
        Console.WriteLine("4. SHOVAN");
        Console.Write("Choose a Class: ");

        string choiceClass = Console.ReadLine();
        string _class = "";

        switch (choiceClass)
        {
            case "1": _class = "AC"; break;
            case "2": _class = "F_SEAT"; break;
            case "3": _class = "S_CHAIR"; break;
            case "4": _class = "SHOVAN"; break;
            default: Console.WriteLine("Invalid Choice!"); return;
        }

        // Calculate Fare
        int fare = CalculateFare(from, to, _class);
        Console.WriteLine($"Fare for this ticket: {fare} TK");

        // Create ticket and add to list
        Ticket ticket = new Ticket(ticketCounter++, name, trainNumber, _class);
        tickets.Add(ticket);

        // Reduce available seats
        selectedTrain.AvailableSeat--;

        Console.WriteLine("Ticket booked successfully!");
    }

    // View Tickets
    public override void ViewBooked()
    {
        Console.WriteLine("\nTicketID   Passenger Name       Train No.            Class");
        Console.WriteLine("--------------------------------------------------------------");

        foreach (var t in tickets)
            t.DisplayTicket();
    }

    // Cancel Ticket
    public override void CancelTicket()
    {
        Console.Write("Enter Ticket ID: ");
        int id = Convert.ToInt32(Console.ReadLine());

        Ticket t = null;

        // Find the ticket manually
        foreach (var ticket in tickets)
        {
            if (ticket.TicketId == id)
            {
                t = ticket;
                break;
            }
        }

        if (t == null || t.Cancelled)
        {
            Console.WriteLine("Ticket not found!");
            return;
        }

        t.Cancelled = true;

        // Find the train manually
        Train tr = null;
        foreach (Train train in trains)
        {
            if (train.TrainNumber == t.TrainNumber)
            {
                tr = train;
                break;
            }
        }

        if (tr != null)
        {
            tr.AvailableSeat++;
        }

        Console.WriteLine("Ticket cancelled successfully!");
    }

}




// MAIN PROGRAM
class Program
{
    static void Main(string[] args)
    {
        Console.WriteLine("\n----->TRAIN TICKET RESERVATION SYSTEM<-----");

        if (!ToLogin.Login())
        {
            Console.WriteLine("Invalid Login!");
            return;
        }

        TrainReservationSystem system = new TrainReservationSystem();

        while (true)
        {
            Console.WriteLine("\n1. View Trains");
            Console.WriteLine("2. Book Ticket");
            Console.WriteLine("3. View Booked Tickets");
            Console.WriteLine("4. Cancel Ticket");
            Console.WriteLine("5. Exit");
            Console.Write("Choose: ");

            int c = Convert.ToInt32(Console.ReadLine());

            switch (c)
            {
                case 1: system.ViewTrains(); break;
                case 2: system.BookTicket(); break;
                case 3: system.ViewBooked(); break;
                case 4: system.CancelTicket(); break;
                case 5: return;
                default: Console.WriteLine("Invalid choice!"); break;
            }
        }
    }
}
