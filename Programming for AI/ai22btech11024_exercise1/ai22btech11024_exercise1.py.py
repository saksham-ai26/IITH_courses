import pandas as pd
import re
from itertools import combinations
#1
print("1")
df = pd.read_csv('shopping.csv')
print(df)

#2
print("2")
dict = {} #creating a dictionary to store the transaction details of each customer with associating a transaction id T1,T2,T3 so on
# Generating transaction IDs and store items in the dictionary
for i,transaction in df.iterrows():
    transaction_id = 'T'+str(i+1) # Generating a transaction ID starting from 'T1'
    transaction_items = transaction.values[1:] # Extracting the items purchased in the transaction
    # Remove NaN values from the transaction items
    transaction_items = [item for item in transaction_items if pd.notnull(item)]
    dict[transaction_id] = transaction_items  # Converting the items to a list and store in the dictionary
for transaction_id, items in list(dict.items())[:5]: # Printing the first five key-value pairs
    print(transaction_id, items)
    df.columns = df.columns.str.strip() # Strip leading and trailing spaces from column names
 
 #3
 # Convert the name of each item to a single format
formatted_items = []
for item in transaction_items:
        # Replace spaces, slashes, and dashes with underscores
        formatted_item = re.sub(r'[\s/\\-]', '_', str(item))
        formatted_items.append(formatted_item)
    
    # Store the formatted items in the dictionary
dict[transaction_id] = formatted_items

# Sort the items in each transaction in lexical order
for items in dict.values():
    items.sort(key=lambda x: str(x))

for transaction_id, items in (dict.items()):
    formatted_items = [re.sub(r'[\s/\\-]', '_', item) for item in items]
    dict[transaction_id] = formatted_items

for transaction_id, items in sorted(dict.items())[:5]:
    formatted_items = [re.sub(r'[\s/\\-]', '_', item) for item in items]


#4
print("4")
# Function to print items for a given transaction ID
def print_items_for_transaction(transaction_id):
    if transaction_id in dict:
        items = dict[transaction_id]
        print(f"Items purchased in transaction {transaction_id}:",end = ' ')
        for item in items:
            print(item, end = ' ')
    else:
        print(f"Transaction ID {transaction_id} does not exist.")

# Call the function to print items for transaction IDs 32, 68, 78
transaction_ids = ['T32', 'T68', 'T78']
for transaction_id in transaction_ids:
    print_items_for_transaction(transaction_id)
    print()

#5
print("5")
# Calculate support for each item
item_support = {}
total_transactions = len(dict)
for key, value in dict.items():
    for item in value:
        if item in item_support:
            item_support[item] += 1
        else:
            item_support[item] = 1

# Generate table for different support thresholds
support_thresholds = [0.5, 1, 2, 3, 5, 10]  # Support thresholds in percentage
support_row = []
items_row = []
frequent_items_support_3 = []
for threshold in support_thresholds:
    frequent_items = []
    for item, support in item_support.items():
        item_support_percent = support / total_transactions * 100
        if item_support_percent >= threshold:
            frequent_items.append(item)
    support_row.append(f"{threshold}%")
    items_row.append(len(frequent_items))
    if (threshold == 3):
        frequent_items_support_3 = frequent_items

# Create pandas DataFrame from support thresholds and items rows
table_data1 = { 'No. of items': items_row}

table_df1 = pd.DataFrame(table_data1,index=['support@0.5', 'support@1', 'support@2', 'support@3', 'support@5', 'support@10'])

table_df1 = table_df1.transpose()
print(table_df1)

print('support@3', f"{frequent_items_support_3}")


two_itemsets = list(combinations(item_support.keys(), 2))

#6
print("6")
# Calculate support for each two-itemset
two_itemset_support = {}
for itemset in two_itemsets:
    count = 0
    for _, value in dict.items():
        if set(itemset).issubset(set(value)):
            count += 1
    two_itemset_support[itemset] = count / total_transactions

# Set support threshold values
support_thresholds = [0.5, 1, 2, 3, 5, 10]
items_row = []
support_row = []
frequent_two_itemsets_3 = []
# Print the most frequent two-itemsets for each support threshold
for threshold in support_thresholds:
    frequent_two_itemsets = {itemset: support for itemset,
                             support in two_itemset_support.items() if support > threshold / 100}
    items_row.append(len(frequent_two_itemsets))
    support_row.append(f"{threshold}%")
    if (threshold == 3):
        frequent_two_itemsets_3 = frequent_two_itemsets


table_data2 = { 'No. of items': items_row}
table_df2 = pd.DataFrame(table_data2, index=['support@0.5', 'support@1', 'support@2', 'support@3', 'support@5', 'support@10'])

table_df2 = table_df2.transpose()
print(table_df2)

print('support@3', f"{frequent_two_itemsets_3.keys()}")




