#pragma once
struct InterfaceManager
{
    public TextMeshPro stateText;
    public TextMeshPro cashText;
    public TextMeshPro timeText;
    public TextMeshPro statesText;
    public TextMeshPro messagesText;
    GameObject actor;
    GameObject messageDispatcher;
    GameObject hungerBar;
    GameObject thirstBar;
    GameObject energyBar;
    GameObject happyBar;
    AgentBehavior agentBehavior;

    public float speed;
    List<GameObject> states = new List<GameObject>();
    List<GameObject> friends = new List<GameObject>();

    // Start is called before the first frame update
    void Start()
    {
        messageDispatcher = GameObject.Find("MessageDispatcher");
        Telegram t = messageDispatcher.GetComponent<Telegram>();
        states = t.states;
        friends = t.friends;
        messagesText.text = "";
        hungerBar = GameObject.Find("Hunger");
        thirstBar = GameObject.Find("Thirst");
        energyBar = GameObject.Find("Energy");
        happyBar = GameObject.Find("Happy");
        actor = GameObject.Find("Character");
        agentBehavior = actor.GetComponent<AgentBehavior>();
        hungerBar.GetComponent<SliderBar>().setValue(8000);
        thirstBar.GetComponent<SliderBar>().setValue(8000);
        energyBar.GetComponent<SliderBar>().setValue(8000);
        happyBar.GetComponent<SliderBar>().setValue(8000);
        
    }

    void Update()
    {
        float hunger = agentBehavior.fullness;
        float thirst = agentBehavior.thirst;
        float energy = agentBehavior.energy;
        float happiness = agentBehavior.happiness;
        cashText.text = "Cash: " + agentBehavior.money.ToString("#");
        stateText.text = agentBehavior.type;
        statesText.text = " Friend 1: " + friends[0].GetComponent<AgentBehavior>().type + "\nFriend 2: " + friends[1].GetComponent<AgentBehavior>().type + "\nFriend 3: " + friends[2].GetComponent<AgentBehavior>().type;
        cashText.text = "Cash: " + actor.GetComponent<AgentBehavior>().money.ToString("#");
        time += Time.deltaTime * 1440.0f * speed;
        clock(time);
        hungerBar.GetComponent<SliderBar>().setCurrentValue(hunger);
        thirstBar.GetComponent<SliderBar>().setCurrentValue(thirst);
        energyBar.GetComponent<SliderBar>().setCurrentValue(energy);
        happyBar.GetComponent<SliderBar>().setCurrentValue(happiness);
    }
    
    void updateMessageText(string msg)
    {
        int numLines = messagesText.text.Split('\n').Length;
        //Remove upper messages
        if (numLines > 6)
        {
            string[] items = messagesText.text.Split('\n');
            messagesText.text = items[1] + "\n" + items[2] + "\n" + items[3] + "\n" + items[4] + "\n" + items[5] + "\n";
        }
        //Add messages to message box
        messagesText.text += msg;
        messagesText.text += "\n";
    }
};
